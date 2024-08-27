from test_base import BaseTest
import json

class MoviesTest(BaseTest):
    def test_create_and_get_single_movie_basic(self):
        response = self.do_post("/movie", {
            "title": "The Test Movie",
            "year": 2024,
            "rating_major": 6,
            "rating_minor": 0,
            "runtime_minutes": 123,
            "cover_image_url": "https://optional.field.com/cover_image.jpg",
            "downloads": [],
            "genres": [],
        })
        self.assertEqual(201, response.status_code)
        self.assertEqual(1, response.json()["id"])
        response = self.do_get("/movie/1")
        self.assertEqual(200, response.status_code)
        response_json = response.json()
        # Validate response
        self.assertEqual("The Test Movie", response_json["title"])
        self.assertEqual(2024, response_json["year"])
        self.assertEqual(None, response_json["synopsis"])
        self.assertEqual(60, response_json["rating"])
        self.assertEqual(123, response_json["runtime_minutes"])
        self.assertEqual("https://optional.field.com/cover_image.jpg", response_json["cover_image_url"])
        self.assertEqual([], response_json["genres"])
        self.assertEqual([], response_json["downloads"])

    def test_create_and_get_single_movie_full(self):
        response = self.do_post("/movie", {
            "title": "The Test Movie",
            "year": 2024,
            "rating_major": 6,
            "rating_minor": 0,
            "runtime_minutes": 123,
            "synopsis": "Optional synopsis",
            "cover_image_url": "https://optional.field.com/cover_image.jpg",
            "downloads": [{
                "quality": 720,
                "size_bytes": 1234,
                "magnet_link": 'some_magnet_link',
                "seeder_count": 123,
                "peer_count": 321,
            }, {
                "quality": 1080,
                "size_bytes": 4321,
                "magnet_link": 'another_magnet_link',
                "seeder_count": 345,
                "peer_count": 543,
            }],
            "genres": [1, 2, 3],
        })
        self.assertEqual(201, response.status_code)
        self.assertEqual(1, response.json()["id"])
        response = self.do_get("/movie/1")
        self.assertEqual(200, response.status_code)
        response_json = response.json()
        # Validate response
        self.assertEqual("The Test Movie", response_json["title"])
        self.assertEqual(2024, response_json["year"])
        self.assertEqual("Optional synopsis", response_json["synopsis"])
        self.assertEqual(60, response_json["rating"])
        self.assertEqual(123, response_json["runtime_minutes"])
        self.assertEqual("https://optional.field.com/cover_image.jpg", response_json["cover_image_url"])
        self.assertEqual([1, 2, 3], response_json["genres"])
        # Validate downloads
        downloads = response_json["downloads"]
        download = [download for download in downloads if download["id"] == 1][0]
        self.assertEqual(720, download["quality"])
        self.assertEqual(1234, download["size_bytes"])
        self.assertEqual("some_magnet_link", download["magnet_link"])
        self.assertEqual(123, download["seeder_count"])
        self.assertEqual(321, download["peer_count"])
        download = [download for download in downloads if download["id"] == 2][0]
        self.assertEqual(1080, download["quality"])
        self.assertEqual(4321, download["size_bytes"])
        self.assertEqual("another_magnet_link", download["magnet_link"])
        self.assertEqual(345, download["seeder_count"])
        self.assertEqual(543, download["peer_count"])
