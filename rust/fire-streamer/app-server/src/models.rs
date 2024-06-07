use super::schema::*;
use diesel::prelude::*;
use serde_derive::Serialize;

#[derive(Queryable, Selectable, Serialize)]
#[diesel(table_name = movies)]
#[diesel(check_for_backend(diesel::sqlite::Sqlite))]
pub struct Movie {
    pub id: i32,
    pub title: String,
    pub year: i32,
    pub synopsis: Option<String>,
    pub rating: i32,
    pub runtime_minutes: i32,
    pub cover_image_url: Option<String>,
}

#[derive(Insertable)]
#[diesel(table_name = movies)]
pub struct NewMovie<'a> {
    pub title: &'a str,
    pub year: i32,
    pub synopsis: Option<&'a str>,
    pub rating: i32,
    pub runtime_minutes: i32,
    pub cover_image_url: Option<&'a str>,
}

#[derive(Queryable, Selectable, Serialize, Associations)]
#[diesel(belongs_to(Movie))]
#[diesel(table_name = downloads)]
#[diesel(check_for_backend(diesel::sqlite::Sqlite))]
pub struct Download {
    pub id: i32,
    pub quality: i32,
    pub size_bytes: i64,
    pub magnet_link: String,
    pub seeder_count: i32,
    pub peer_count: i32,
    pub movie_id: i32,
}
