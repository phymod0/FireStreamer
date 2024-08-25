#!/bin/python

import os
import requests
from dotenv import load_dotenv
from sources.yts_mx import YtsMxSource

load_dotenv()

mms_endpoint = os.getenv("MMS_ENDPOINT")
mms_port = os.getenv("MMS_PORT")
if mms_endpoint is None or mms_port is None:
    print("MovieMetadataService endpoint unconfigured, aborting...")
    exit(1)

def upload_movie(movie, endpoint, port):
    requests.post(f"http://{endpoint}:{port}/movie", json={
        "title": movie.title,
        "year": movie.year,
        "rating_major": movie.rating_major,
        "rating_minor": movie.rating_minor,
        "runtime_minutes": movie.runtime_minutes,
        "synopsis": movie.synopsis,
        "cover_image_url": movie.cover_image_url,
        "genres": [genre.value for genre in movie.genres],
        "downloads": [{
            "quality": download.quality.value,
            "size_bytes": download.size_bytes,
            "magnet_link": download.magnet_link,
            "seeder_count": download.seeder_count,
            "peer_count": download.peer_count,
        } for download in movie.downloads],
    })

source = YtsMxSource()
movies = source.next_page(0)
for movie in movies:
    print(movie.debug())
    upload_movie(movie, mms_endpoint, mms_port)
