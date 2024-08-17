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
            # "synopsis": "Optional synopsis",
            # "cover_image_url": "https://optional.field.com/cover_image.jpg",
            "downloads": [],
            "genres": [],
        })
        self.assertEqual(201, response.status_code)
        self.assertEqual(1, response.json()["id"])
