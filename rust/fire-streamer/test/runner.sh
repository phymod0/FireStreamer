#!/bin/bash

RUST_PROJECT_PATH=".."
APP_SERVER_PATH="$RUST_PROJECT_PATH/app-server"
MOVIE_COLLECTOR_PATH="$RUST_PROJECT_PATH/movie-collector"

function start_test_server() {
    (cd "$APP_SERVER_PATH" && cargo run) &
    TEST_SERVER_PID=$!
    sleep 1
}

function stop_test_server() {
    kill -SIGINT $TEST_SERVER_PID
}

start_test_server
python run_tests.py
stop_test_server
