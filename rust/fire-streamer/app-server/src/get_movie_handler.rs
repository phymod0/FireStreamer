use axum::{extract::Path, http::StatusCode};
use diesel::prelude::*;
use serde_json::{json, Value as Json};
use tracing::*;

use crate::{
    common::{connect_db, HandlerResponse},
    errors::AppError,
    models::*,
    schema::movie_genres::dsl as genres,
    schema::movies::dsl as movies,
};

type AxumJson = axum::Json<Json>;

fn get_movie_by_id(db: &mut SqliteConnection, id: i32) -> Result<Movie, AppError> {
    let results = movies::movies
        .filter(movies::id.eq(id))
        .select(Movie::as_select())
        .load(db)?;
    if results.len() > 1 {
        warn!("Got multiple results for movie ID {}", id);
    }
    results.into_iter().next().ok_or_else(|| {
        warn!("Did not get any results for movie ID {}", id);
        AppError::ResourceNotFoundError
    })
}

fn get_genres_for_movie_id(db: &mut SqliteConnection, id: i32) -> Result<Vec<i32>, AppError> {
    Ok(genres::movie_genres
        .filter(genres::movie_id.eq(id))
        .select(MovieGenreAssociation::as_select())
        .load(db)?
        .iter()
        .map(|assoc| assoc.genre)
        .collect())
}

fn get_movie_json(id: i32) -> Result<AxumJson, AppError> {
    let db = &mut connect_db()?;
    let mut movie_json = serde_json::to_value(get_movie_by_id(db, id)?).unwrap();
    movie_json["genres"] = json!(get_genres_for_movie_id(db, id)?);
    Ok(axum::Json(movie_json))
}

pub async fn handler(Path(movie_id): Path<i32>) -> HandlerResponse<AxumJson> {
    debug!("Get movie handler called with parameters: {}", movie_id);
    Ok((StatusCode::OK, get_movie_json(movie_id)?))
}
