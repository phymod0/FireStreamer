#!/usr/bin/env python3
from http.server import HTTPServer, CGIHTTPRequestHandler
import time
import os

PORT=8080
SHUTDOWN_FILE="/tmp/stop_firestreamer_test_server"
CGI_DIR="/cgi-bin"
CACHE_EXPIRY_SECS=1

last_checked_time = 0
cached_result = False

def should_stop_server():
    global last_checked_time, cached_result
    current_time = time.time()
    if current_time - last_checked_time < 1:
        return cached_result
    cached_result = os.path.exists(SHUTDOWN_FILE)
    last_checked_time = current_time
    return cached_result

server_address = ('', PORT)
CGIHTTPRequestHandler.cgi_directories = [CGI_DIR]
httpd = HTTPServer(server_address, CGIHTTPRequestHandler)
httpd.timeout = 1
try:
    while not should_stop_server():
        httpd.handle_request()
except KeyboardInterrupt:
    httpd.socket.close()
