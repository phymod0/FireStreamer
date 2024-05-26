// @generated automatically by Diesel CLI.

diesel::table! {
    movies (id) {
        id -> Integer,
        title -> Text,
        year -> Nullable<Integer>,
        rating -> Nullable<Integer>,
        cover_image_url -> Nullable<Text>,
        magnet_link -> Nullable<Text>,
    }
}
