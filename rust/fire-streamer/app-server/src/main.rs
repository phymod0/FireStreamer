mod models;
mod schema;
mod errors;
mod common;
mod constants;

// Handlers
mod get_movie_handler;
mod get_movies_handler;
mod add_movie_handler;

#[tokio::main]
async fn main() {
    use axum::routing::{get, post};
    dotenvy::dotenv().ok();
    tracing_subscriber::fmt::init();

    let app = axum::Router::new()
        .route("/movie/:movie_id", get(get_movie_handler::handler))
        .route("/movies", get(get_movies_handler::handler))
        .route("/movie", post(add_movie_handler::handler));

    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000").await.unwrap();
    axum::serve(listener, app).await.unwrap();
}
