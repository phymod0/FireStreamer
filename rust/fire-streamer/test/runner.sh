#!/bin/bash

RUST_PROJECT_PATH=".."
APP_SERVER_PATH="$RUST_PROJECT_PATH/app-server"
MOVIE_COLLECTOR_PATH="$RUST_PROJECT_PATH/movie-collector"
export DATABASE_URL="$(pwd)/test_db.db"

function create_test_db() {
    local wd=$(pwd)
    cd "$APP_SERVER_PATH"
    diesel migration run
    cd "$wd"
}

function destroy_test_db() {
    rm -rf "$DATABASE_URL"
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
