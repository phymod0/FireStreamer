CREATE TABLE movie_genres (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    movie_id INTEGER NOT NULL REFERENCES movies(id),
    genre INT NOT NULL
)
