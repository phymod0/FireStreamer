use axum::{http::StatusCode, Json};
use diesel::prelude::*;
use serde_derive::{Deserialize, Serialize};
use tracing::*;

use crate::{
    common::{connect_db, last_insert_rowid, HandlerResponse},
    constants::{validate, Genre, Quality},
    errors::AppError,
    models::*,
    schema::{downloads, movie_genres, movies},
};

#[derive(Deserialize, Debug)]
struct AddMovieRequestDownload {
    quality: u32,
    size_bytes: u64,
    magnet_link: String,
    seeder_count: u32,
    peer_count: u32,
}

#[derive(Deserialize, Debug)]
pub struct AddMovieRequest {
    title: String,
    year: u32,
    synopsis: Option<String>,
    rating_major: u32,
    rating_minor: u32,
    runtime_minutes: u32,
    cover_image_url: Option<String>,
    downloads: Vec<AddMovieRequestDownload>,
    genres: Vec<u32>,
}

#[derive(Serialize)]
pub struct AddMovieResponse {
    id: i32,
}

fn add_movie(
    req: &AddMovieRequest,
    db: &mut SqliteConnection,
) -> Result<AddMovieResponse, AppError> {
    let movie = NewMovie {
        title: &req.title,
        year: req.year as i32,
        synopsis: req.synopsis.as_ref().map(|s| s.as_str()),
        rating: (req.rating_major * 10 + req.rating_minor) as i32,
        runtime_minutes: req.runtime_minutes as i32,
        cover_image_url: req.cover_image_url.as_ref().map(|s| s.as_str()),
    };
    diesel::insert_into(movies::table)
        .values(movie)
        .execute(db)?;
    let movie_id: i32 = diesel::select(last_insert_rowid()).get_result::<i32>(db)?;
    for genre in &req.genres {
        let genre_association = NewMovieGenreAssociation {
            genre: validate::<Genre>(*genre)?,
            movie_id,
        };
        diesel::insert_into(movie_genres::table)
            .values(&genre_association)
            .execute(db)?;
    }
    for download in &req.downloads {
        let new_download = NewDownload {
            quality: validate::<Quality>(download.quality)?,
            size_bytes: download.size_bytes as i64,
            magnet_link: &download.magnet_link,
            seeder_count: download.seeder_count as i32,
            peer_count: download.peer_count as i32,
            movie_id,
        };
        diesel::insert_into(downloads::table)
            .values(&new_download)
            .execute(db)?;
    }
    Ok(AddMovieResponse { id: movie_id })
}

pub async fn handler(Json(req): Json<AddMovieRequest>) -> HandlerResponse<Json<AddMovieResponse>> {
    debug!("Add movie handler called with parameters: \"{:#?}\"", req);
    let result =
        connect_db()?.transaction::<AddMovieResponse, AppError, _>(|conn| add_movie(&req, conn))?;
    Ok((StatusCode::CREATED, Json(result)))
}
