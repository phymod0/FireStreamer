use axum::{extract::Path, http::StatusCode, Json};
use diesel::prelude::*;
use tracing::*;

use crate::{
    common::{connect_db, HandlerResponse},
    errors::AppError,
    models::*,
    schema::movies::dsl::*,
};

fn get_movie(movie_id: i32) -> Result<Movie, AppError> {
    let db = &mut connect_db()?;
    let results = movies
        .filter(id.eq(movie_id))
        .select(Movie::as_select())
        .load(db)?;
    if results.len() > 1 {
        warn!("Got multiple results for movie ID {}", movie_id);
    }
    results.into_iter().next().ok_or_else(|| {
        warn!("Did not get any results for movie ID {}", movie_id);
        AppError::ResourceNotFoundError
    })
}

pub async fn handler(Path(movie_id): Path<i32>) -> HandlerResponse<Json<Movie>> {
    debug!("Get movie handler called with parameters: {}", movie_id);
    Ok((StatusCode::OK, Json(get_movie(movie_id)?)))
}
