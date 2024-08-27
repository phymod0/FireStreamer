from enum import Enum, auto

class Genre(Enum):
    ACTION = auto()
    ADVENTURE = auto()
    ANIMATION = auto()
    BIOGRAPHY = auto()
    COMEDY = auto()
    CRIME = auto()
    DOCUMENTARY = auto()
    DRAMA = auto()
    FAMILY = auto()
    FANTASY = auto()
    HISTORY = auto()
    HORROR = auto()
    MUSIC = auto()
    MUSICAL = auto()
    MYSTERY = auto()
    ROMANCE = auto()
    SCI_FI = auto()
    SPORT = auto()
    THRILLER = auto()
    WAR = auto()
    WESTERN = auto()

POSSIBLE_SCIFI_NAMES = ["SCI-FI", "SCI_FI", "SCIFI"]

def get_genre_by_name(name):
    name = name.strip().upper()
    if name in POSSIBLE_SCIFI_NAMES:
        return Genre.SCI_FI
    return getattr(Genre, name)

class Movie:
    def __init__(self,
                 title,
                 year,
                 synopsis,
                 rating_major,
                 rating_minor,
                 runtime_minutes,
                 cover_image_url,
                 downloads,
                 genres):
        self.title = title
        self.year = year
        self.synopsis = synopsis
        self.rating_major = rating_major
        self.rating_minor = rating_minor
        self.runtime_minutes = runtime_minutes
        self.cover_image_url = cover_image_url
        self.downloads = downloads
        self.genres = genres

    def debug(self):
        result = ""
        result += f"{self.title} ({self.year})\n"
        result += f"    Summary: {self.synopsis}\n"
        result += f"    Rating: {self.rating_major}.{self.rating_minor}\n"
        result += f"    Length: {self.runtime_minutes} minutes\n"
        result += f"    Genres:\n"
        for genre in self.genres:
            result += f"        - {genre}\n"
        result += f"    Cover image link: {self.cover_image_url}\n"
        result += f"    Downloads:\n"
        for download in self.downloads:
            result += f"        - {download.debug(indent=12)}\n"
        if len(result) and result[-1] == '\n':
            result = result[:-1]
        return result

class MovieBuilder:
    def __init__(self):
        self.__title = None
        self.__year = None
        self.__synopsis = None
        self.__rating_major = None
        self.__rating_minor = None
        self.__runtime_minutes = None
        self.__cover_image_url = None
        self.__downloads = []
        self.__genres = set()
        pass

    def set_title(self, title):
        self.__title = title

    def set_year(self, year):
        self.__year = int(year)

    def set_synopsis(self, synopsis):
        self.__synopsis = synopsis

    def set_rating(self, rating):
        rating = int(float(rating) * 10)
        self.__rating_major = rating // 10
        self.__rating_minor = rating % 10

    def set_runtime_minutes(self, runtime_minutes):
        self.__runtime_minutes = int(runtime_minutes)

    def set_cover_image_url(self, cover_image_url):
        self.__cover_image_url = cover_image_url

    def add_download(self, download):
        self.__downloads.append(download)

    def add_genre(self, genre):
        genre = get_genre_by_name(genre)
        if genre is not None:
            self.__genres.add(genre)

    def build(self):
        return Movie(
            self.__title,
            self.__year,
            self.__synopsis,
            self.__rating_major,
            self.__rating_minor,
            self.__runtime_minutes,
            self.__cover_image_url,
            self.__downloads,
            self.__genres
        )
