use super::schema::*;
use diesel::prelude::*;
use serde_derive::Serialize;

#[derive(Queryable, Selectable, Serialize)]
#[diesel(table_name = movies)]
#[diesel(check_for_backend(diesel::sqlite::Sqlite))]
pub struct Movie {
    pub id: i32,
    pub title: String,
    pub year: Option<i32>,
    pub rating: Option<i32>,
    pub cover_image_url: Option<String>,
}

#[derive(Insertable)]
#[diesel(table_name = movies)]
pub struct NewMovie<'a> {
    pub title: &'a str,
}

#[derive(Queryable, Selectable, Serialize, Associations)]
#[diesel(belongs_to(Movie))]
#[diesel(table_name = downloads)]
#[diesel(check_for_backend(diesel::sqlite::Sqlite))]
pub struct Download {
    pub id: i32,
    pub quality: Option<i32>,
    pub size_bytes: Option<i32>,
    pub magnet_link: Option<String>,
    pub seeder_count: Option<i32>,
    pub peer_count: Option<i32>,
    pub movie_id: i32,
}
