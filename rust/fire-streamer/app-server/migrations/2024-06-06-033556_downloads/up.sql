CREATE TABLE downloads (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    quality INT,
    size_bytes INT,
    magnet_link VARCHAR(4096),
    seeder_count INT,
    peer_count INT,
    movie_id INTEGER NOT NULL REFERENCES movies(id)
)
