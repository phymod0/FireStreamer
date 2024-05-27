use std::env;
use axum::http::StatusCode;
use diesel::prelude::*;
use crate::errors::AppError;

pub type HandlerResponse<T> = Result<(StatusCode, T), StatusCode>;

sql_function!(fn last_insert_rowid() -> diesel::sql_types::Integer);

pub fn connect_db() -> Result<SqliteConnection, AppError> {
    let database_url = env::var("DATABASE_URL")?;
    Ok(SqliteConnection::establish(&database_url)?)
}
