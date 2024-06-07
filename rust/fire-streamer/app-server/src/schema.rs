// @generated automatically by Diesel CLI.

diesel::table! {
    downloads (id) {
        id -> Integer,
        quality -> Integer,
        size_bytes -> BigInt,
        magnet_link -> Text,
        seeder_count -> Integer,
        peer_count -> Integer,
        movie_id -> Integer,
    }
}

diesel::table! {
    movie_genres (id) {
        id -> Integer,
        movie_id -> Integer,
        genre -> Integer,
    }
}

diesel::table! {
    movies (id) {
        id -> Integer,
        title -> Text,
        year -> Integer,
        synopsis -> Nullable<Text>,
        rating -> Integer,
        runtime_minutes -> Integer,
        cover_image_url -> Nullable<Text>,
    }
}

diesel::joinable!(downloads -> movies (movie_id));
diesel::joinable!(movie_genres -> movies (movie_id));

diesel::allow_tables_to_appear_in_same_query!(
    downloads,
    movie_genres,
    movies,
);
