from urllib.parse import quote_plus

import requests
import json

from utils import URLQueryBuilder
from movie import MovieBuilder
from download import DownloadBuilder
from sources.source_base import SourceBase

YTS_ENDPOINT="https://yts.mx/api/v2/list_movies.json"
MAX_PAGE_SIZE = 50
PAGE_SIZE = MAX_PAGE_SIZE
DELAY_MS = 200

# See https://yts.mx/api
TRACKERS = [
    "udp://open.demonii.com:1337/announce",
    "udp://tracker.openbittorrent.com:80",
    "udp://tracker.coppersurfer.tk:6969",
    "udp://glotorrents.pw:6969/announce",
    "udp://tracker.opentrackr.org:1337/announce",
    "udp://torrent.gresille.org:80/announce",
    "udp://p4p.arenabg.com:1337",
    "udp://tracker.leechers-paradise.org:6969"
]

def get_magnet_link(torrent_name, torrent_hash):
    url_encoded_name = quote_plus(torrent_name)
    hash_param = f"xt=urn:btih:{torrent_hash}"
    name_param = f"dn={url_encoded_name}"
    tracker_params = [f"tr={link}" for link in TRACKERS]
    magnet_params = [hash_param, name_param] + tracker_params
    return "magnet:?" + "&".join(magnet_params)

def build_url_query(page_idx, page_size=PAGE_SIZE, endpoint=YTS_ENDPOINT):
    page_number = page_idx + 1
    uqb = URLQueryBuilder(endpoint)
    uqb.add_param("limit", page_size)
    uqb.add_param("page", page_number)
    uqb.add_param("order_by", "asc")
    return uqb.build()

def build_movie_from_json(movie_json):
    mb = MovieBuilder()
    title = movie_json["title"]
    year = movie_json["year"]
    title_year = f"{title} ({year})"
    mb.set_title(title)
    mb.set_year(year)
    mb.set_synopsis(movie_json["description_full"])
    mb.set_rating(movie_json["rating"])
    mb.set_runtime_minutes(movie_json["runtime"])
    mb.set_cover_image_url(movie_json["large_cover_image"])
    for torrent in movie_json["torrents"]:
        db = DownloadBuilder()
        db.set_quality(torrent["quality"])
        db.set_size_bytes(torrent["size_bytes"])
        db.set_magnet_link(get_magnet_link(title_year, torrent["hash"]))
        db.set_seeder_count(torrent["seeds"])
        db.set_peer_count(torrent["peers"])
        mb.add_download(db.build())
    for genre in movie_json["genres"]:
        mb.add_genre(genre)
    return mb.build()

class YtsMxSource(SourceBase):
    def __init__(self):
        pass

    def next_page(self, page_idx):
        query = build_url_query(page_idx)
        response = requests.get(query)
        if response.status_code != 200:
            raise Exception(f"YTS.MX query failed for page index {page_idx}")
        result = json.loads(response.text)
        movies = result["data"]["movies"]
        return [build_movie_from_json(movie) for movie in movies]
