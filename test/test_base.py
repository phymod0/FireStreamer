from unittest import TestCase
import requests
import os
import shutil

TEST_SERVER_PORT="3000"

class BaseTest(TestCase):
    @classmethod
    def setUpClass(cls):
        pass

    @classmethod
    def tearDownClass(cls):
        pass

    def setUp(self):
        db_path = os.getenv('DATABASE_URL')
        blank_path = os.getenv('BLANK_DB_BACKUP')
        shutil.copy(blank_path, db_path)

    def tearDown(self):
        pass

    def do_get(self, resource):
        return requests.get('http://localhost:' + TEST_SERVER_PORT + '/' + resource)

    def do_post(self, resource, body=None):
        return requests.post('http://localhost:' + TEST_SERVER_PORT + '/' + resource, json=body)
