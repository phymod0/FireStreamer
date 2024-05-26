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
    pub magnet_link: Option<String>,
}

#[derive(Insertable)]
#[diesel(table_name = movies)]
pub struct NewMovie<'a> {
    pub title: &'a str,
}
