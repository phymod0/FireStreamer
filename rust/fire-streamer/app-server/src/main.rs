pub mod models;
pub mod schema;

use dotenvy::dotenv;
use std::env;

use serde_derive::{Deserialize, Serialize};
use diesel::prelude::*;
use tracing::*;

use axum::{
    routing::{get, post},
    http::StatusCode,
    extract::Path,
    Json, Router,
};
use models::*;

sql_function!(fn last_insert_rowid() -> diesel::sql_types::Integer);

fn connect_db() -> SqliteConnection {
    let database_url = env::var("DATABASE_URL").expect("DATABASE_URL must be set");
    SqliteConnection::establish(&database_url)
        .unwrap_or_else(|_| panic!("Error connecting to {}", database_url))
}

#[tokio::main]
async fn main() {
    dotenv().ok();
    tracing_subscriber::fmt::init();

    let app = Router::new()
        .route("/movie/:movie_id", get(get_movie))
        .route("/movies", get(get_movies))
        .route("/movie", post(add_movie));

    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000").await.unwrap();
    axum::serve(listener, app).await.unwrap();
}

async fn get_movie(Path(movie_id): Path<i32>) -> Result<(StatusCode, Json<Movie>), StatusCode> {
    use schema::movies::dsl::*;
    debug!("Handler called: get_movie({})", movie_id);
    let db = &mut connect_db();
    let results = movies
        .filter(id.eq(movie_id))
        .select(Movie::as_select())
        .load(db)
        .expect("Error loading movies");
    if results.len() > 1 {
        warn!("Got multiple results for movie ID {}", movie_id);
    }
    match results.into_iter().next() {
        Some(result) => Ok((StatusCode::OK, Json(result))),
        None => {
            warn!("Did not get any results for movie ID {}", movie_id);
            Err(StatusCode::NOT_FOUND)
        },
    }
}

async fn get_movies() -> (StatusCode, Json<Vec<Movie>>) {
    use schema::movies::dsl::*;
    debug!("Handler called: get_movies()");
    let db = &mut connect_db();
    let results = movies
        .limit(50)
        .select(Movie::as_select())
        .load(db)
        .expect("Error loading movies");
    debug!("Returning {} results", results.len());
    (StatusCode::OK, Json(results))
}

#[derive(Deserialize)]
struct AddMovieRequest {
    title: String,
}

#[derive(Serialize)]
struct AddMovieResponse {
    id: i32,
}

async fn add_movie(
    Json(req): Json<AddMovieRequest>,
) -> (StatusCode, Json<AddMovieResponse>) {
    use schema::movies;
    debug!("Handler called: add_movie(\"{}\")", req.title);
    let movie = NewMovie {
        title: req.title.as_str(),
    };
    let db = &mut connect_db();
    diesel::insert_into(movies::table)
        .values(&movie)
        .execute(db)
        .expect("Failed to insert movie");
    let id: i32 = diesel::select(last_insert_rowid())
        .get_result::<i32>(db)
        .expect("Error getting last inserted id");
    (StatusCode::CREATED, Json(AddMovieResponse { id }))
}
