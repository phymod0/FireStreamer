use axum::http::StatusCode;
use tracing::error;

#[derive(Debug)]
pub enum AppError {
    EnvironmentVariableUndeclaredError(std::env::VarError),
    DatabaseConnectionError(diesel::prelude::ConnectionError),
    DatabaseError(diesel::result::Error),
    UnmappedInputError(i32, &'static str),
    ResourceNotFoundError,
}

impl From<std::env::VarError> for AppError {
    fn from(err: std::env::VarError) -> AppError {
        error!("Failed to access environment variable");
        AppError::EnvironmentVariableUndeclaredError(err)
    }
}

impl From<diesel::prelude::ConnectionError> for AppError {
    fn from(err: diesel::prelude::ConnectionError) -> AppError {
        error!("Failed to establish database connection");
        AppError::DatabaseConnectionError(err)
    }
}

impl From<diesel::result::Error> for AppError {
    fn from(err: diesel::result::Error) -> AppError {
        error!("Failed to transact with database");
        AppError::DatabaseError(err)
    }
}

impl From<AppError> for StatusCode {
    fn from(err: AppError) -> StatusCode {
        match err {
            /* Runtime errors */
            AppError::EnvironmentVariableUndeclaredError(_)
            | AppError::DatabaseConnectionError(_)
            | AppError::DatabaseError(_) => StatusCode::INTERNAL_SERVER_ERROR,
            /* User errors */
            AppError::UnmappedInputError(_, _) => StatusCode::BAD_REQUEST,
            AppError::ResourceNotFoundError => StatusCode::NOT_FOUND,
        }
    }
}
