// @generated automatically by Diesel CLI.

diesel::table! {
    downloads (id) {
        id -> Integer,
        quality -> Nullable<Integer>,
        size_bytes -> Nullable<Integer>,
        magnet_link -> Nullable<Text>,
        seeder_count -> Nullable<Integer>,
        peer_count -> Nullable<Integer>,
        movie_id -> Integer,
    }
}

diesel::table! {
    movies (id) {
        id -> Integer,
        title -> Text,
        year -> Nullable<Integer>,
        rating -> Nullable<Integer>,
        cover_image_url -> Nullable<Text>,
    }
}

diesel::joinable!(downloads -> movies (movie_id));

diesel::allow_tables_to_appear_in_same_query!(
    downloads,
    movies,
);
