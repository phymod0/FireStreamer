use serde_derive::{Deserialize, Serialize};
use diesel::prelude::*;
use tracing::*;
use axum::{
    Json,
    http::StatusCode,
};

use crate::{
    models::*,
    errors::AppError,
    schema::movies,
    common::{
        HandlerResponse,
        last_insert_rowid,
        connect_db,
    },
};

#[derive(Deserialize, Debug)]
struct AddMovieRequestDownload {
    quality: String,
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
    genres: Vec<String>,
}

impl<'a> From<&'a AddMovieRequest> for NewMovie<'a> {
    fn from(movie: &'a AddMovieRequest) -> Self {
        Self {
            title: &movie.title,
            year: movie.year as i32,
            synopsis: movie.synopsis.as_ref().map(|s| s.as_str()),
            rating: (movie.rating_major * 10 + movie.rating_minor) as i32,
            runtime_minutes: movie.runtime_minutes as i32,
            cover_image_url: movie.cover_image_url.as_ref().map(|s| s.as_str()),
        }
    }
}

#[derive(Serialize)]
pub struct AddMovieResponse {
    id: i32,
}

fn add_movie(req: &AddMovieRequest) -> Result<AddMovieResponse, AppError> {
    let movie: NewMovie = req.into();
    let db = &mut connect_db()?;
    // TODO(phymod0): Populate genres and downloads too
    diesel::insert_into(movies::table).values(movie).execute(db)?;
    let id: i32 = diesel::select(last_insert_rowid()).get_result::<i32>(db)?;
    Ok(AddMovieResponse { id })
}

pub async fn handler(
    Json(req): Json<AddMovieRequest>,
) -> HandlerResponse<Json<AddMovieResponse>> {
    debug!("Add movie handler called with parameters: \"{:#?}\"", req);
    Ok((StatusCode::CREATED, Json(add_movie(&req)?)))
}