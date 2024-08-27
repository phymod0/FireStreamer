CREATE TABLE movies (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    title VARCHAR(255) NOT NULL,
    year INT NOT NULL,
    synopsis TEXT,
    rating INT NOT NULL,
    runtime_minutes INT NOT NULL,
    cover_image_url VARCHAR(4096)
)
