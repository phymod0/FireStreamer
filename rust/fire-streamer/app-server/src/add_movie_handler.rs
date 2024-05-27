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

#[derive(Deserialize)]
pub struct AddMovieRequest {
    title: String,
}

#[derive(Serialize)]
pub struct AddMovieResponse {
    id: i32,
}

fn add_movie(title: &str) -> Result<AddMovieResponse, AppError> {
    let movie = NewMovie { title };
    let db = &mut connect_db()?;
    diesel::insert_into(movies::table).values(&movie).execute(db)?;
    let id: i32 = diesel::select(last_insert_rowid()).get_result::<i32>(db)?;
    Ok(AddMovieResponse { id })
}

pub async fn handler(
    Json(req): Json<AddMovieRequest>,
) -> HandlerResponse<Json<AddMovieResponse>> {
    let title = req.title;
    debug!("Add movie handler called with parameters: \"{}\"", title);
    Ok((StatusCode::CREATED, Json(add_movie(&title)?)))
}
