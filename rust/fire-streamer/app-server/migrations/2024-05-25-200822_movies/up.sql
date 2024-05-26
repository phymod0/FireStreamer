CREATE TABLE movies (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    title VARCHAR(255) NOT NULL,
    year INT,
    rating INT,
    cover_image_url VARCHAR(255),
    magnet_link VARCHAR(255)
)
