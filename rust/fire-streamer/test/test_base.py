from unittest import TestCase
import requests

TEST_SERVER_PORT="3000"

class BaseTest(TestCase):
    @classmethod
    def setUpClass(cls):
        # Code to run once before all tests
        pass

    @classmethod
    def tearDownClass(cls):
        # Code to run once after all tests
        pass

    def setUp(self):
        # Code to run before each test
        pass

    def tearDown(self):
        # Code to run after each test
        pass

    def do_get(self, resource):
        return requests.get('http://localhost:' + TEST_SERVER_PORT + '/' + resource)

    def do_post(self, resource):
        return requests.post('http://localhost:' + TEST_SERVER_PORT + '/' + resource)
