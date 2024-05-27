use diesel::prelude::*;
use tracing::*;
use axum::{
    Json,
    http::StatusCode,
    extract::Path,
};

use crate::{
    models::*,
    errors::AppError,
    schema::movies::dsl::*,
    common::{
        HandlerResponse,
        connect_db,
    },
};

fn get_movie(movie_id: i32) -> Result<Movie, AppError> {
    let db = &mut connect_db()?;
    let results = movies.filter(id.eq(movie_id)).select(Movie::as_select()).load(db)?;
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
