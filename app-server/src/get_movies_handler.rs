use axum::{http::StatusCode, Json};
use diesel::prelude::*;
use tracing::*;

use crate::{
    common::{connect_db, HandlerResponse},
    errors::AppError,
    models::*,
    schema::movies::dsl::*,
};

fn get_movies() -> Result<Vec<Movie>, AppError> {
    let db = &mut connect_db()?;
    Ok(movies
        .order(year)
        .limit(10)
        .select(Movie::as_select())
        .load(db)?)
}

pub async fn handler() -> HandlerResponse<Json<Vec<Movie>>> {
    debug!("Get movies handler called");
    let results = get_movies()?;
    debug!("Returning {} results", results.len());
    Ok((StatusCode::OK, Json(results)))
}
