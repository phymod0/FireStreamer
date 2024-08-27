CREATE TABLE downloads (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    quality INT NOT NULL,
    size_bytes BIGINT NOT NULL,
    magnet_link VARCHAR(4096) NOT NULL,
    seeder_count INT NOT NULL,
    peer_count INT NOT NULL,
    movie_id INTEGER NOT NULL REFERENCES movies(id)
)
