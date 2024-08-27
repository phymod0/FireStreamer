use diesel::prelude::*;
use tracing::*;
use axum::{
    Json,
    http::StatusCode,
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

fn get_movies() -> Result<Vec<Movie>, AppError> {
    let db = &mut connect_db()?;
    Ok(movies.limit(50).select(Movie::as_select()).load(db)?)
}

pub async fn handler() -> HandlerResponse<Json<Vec<Movie>>> {
    debug!("Get movies handler called");
    let results = get_movies()?;
    debug!("Returning {} results", results.len());
    Ok((StatusCode::OK, Json(results)))
}
