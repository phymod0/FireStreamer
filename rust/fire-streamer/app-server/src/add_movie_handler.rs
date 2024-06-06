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
    synopsis: String,
    rating_major: u32,
    rating_minor: u32,
    runtime_minutes: u32,
    cover_image_url: Option<String>,
    downloads: Vec<AddMovieRequestDownload>,
    genres: Vec<String>,
}

#[derive(Serialize)]
pub struct AddMovieResponse {
    id: i32,
}

fn add_movie(req: AddMovieRequest) -> Result<AddMovieResponse, AppError> {
    let movie = NewMovie {
        title: &req.title,
        year: req.year as i32,
        rating: (req.rating_major * 10 + req.rating_minor) as i32,
        cover_image_url: req.cover_image_url.as_ref().map(|s| s.as_str()),
    };
    let db = &mut connect_db()?;
    diesel::insert_into(movies::table).values(&movie).execute(db)?;
    let id: i32 = diesel::select(last_insert_rowid()).get_result::<i32>(db)?;
    Ok(AddMovieResponse { id })
}

pub async fn handler(
    Json(req): Json<AddMovieRequest>,
) -> HandlerResponse<Json<AddMovieResponse>> {
    debug!("Add movie handler called with parameters: \"{:#?}\"", req);
    Ok((StatusCode::CREATED, Json(add_movie(req)?)))
}
