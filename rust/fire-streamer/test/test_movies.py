from test_base import BaseTest

class MoviesTest(BaseTest):
    def test_example(self):
        # self.assertEqual(1 + 1, 2)
        response = self.do_get("/hi")
        print("Got test response: " + str(response))
