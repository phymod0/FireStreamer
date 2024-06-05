import os
from dotenv import load_dotenv
from sources.yts_mx import YtsMxSource

load_dotenv()

source = YtsMxSource()
movies = source.next_page(0)
for movie in movies:
    print(movie.debug())
