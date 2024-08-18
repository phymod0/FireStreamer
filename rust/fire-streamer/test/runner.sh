#!/bin/bash

RUST_PROJECT_PATH=".."
APP_SERVER_PATH="$RUST_PROJECT_PATH/app-server"
MOVIE_COLLECTOR_PATH="$RUST_PROJECT_PATH/movie-collector"
export BLANK_DB_BACKUP="$(pwd)/blank_backup.db"
export DATABASE_URL="$(pwd)/test_db.db"
export RUST_LOG="warn"

function create_test_db() {
    local wd=$(pwd)
    cd "$APP_SERVER_PATH"
    diesel migration run
    cp "$DATABASE_URL" "$BLANK_DB_BACKUP"
    cd "$wd"
}

function destroy_test_db() {
    rm -rf "$DATABASE_URL"
    rm -rf "$BLANK_DB_BACKUP"
}

function start_test_server() {
    local wd=$(pwd)
    cd "$APP_SERVER_PATH" && cargo build
    (cd "$APP_SERVER_PATH" && cargo run) &
    TEST_SERVER_PID=$!
    cd "$wd"
    sleep 1
}

function stop_test_server() {
    kill -SIGINT $TEST_SERVER_PID
}

create_test_db
start_test_server
python run_tests.py
stop_test_server
destroy_test_db
