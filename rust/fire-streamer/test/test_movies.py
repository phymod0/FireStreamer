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
        self.assertFalse("downloads" in response_json)

    def test_create_and_get_single_movie_full(self):
        response = self.do_post("/movie", {
            "title": "The Test Movie",
            "year": 2024,
            "rating_major": 6,
            "rating_minor": 0,
            "runtime_minutes": 123,
            "synopsis": "Optional synopsis",
            "cover_image_url": "https://optional.field.com/cover_image.jpg",
            "downloads": [],
            "genres": [],
        })
        self.assertEqual(201, response.status_code)
        self.assertEqual(1, response.json()["id"])
        # TODO(phymod0): Assert correctness of response
