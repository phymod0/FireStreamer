use crate::errors::AppError;
use std::convert::TryFrom;

pub enum Quality {
    ThreeDimensional,
    P(i32),
}

impl TryFrom<i32> for Quality {
    type Error = AppError;

    fn try_from(val: i32) -> Result<Self, AppError> {
        match val {
            3 => Ok(Self::ThreeDimensional),
            720 | 1080 | 2160 => Ok(Self::P(val)),
            _ => Err(AppError::UnmappedInputError(val, "Quality")),
        }
    }
}

pub enum VideoSource {
    WebRip,
    BluRay,
}

impl TryFrom<i32> for VideoSource {
    type Error = AppError;

    fn try_from(val: i32) -> Result<Self, AppError> {
        match val {
            1 => Ok(Self::WebRip),
            2 => Ok(Self::BluRay),
            _ => Err(AppError::UnmappedInputError(val, "VideoSource")),
        }
    }
}

pub enum Genre {
    Action,
    Adventure,
    Animation,
    Biography,
    Comedy,
    Crime,
    Documentary,
    Drama,
    Family,
    Fantasy,
    History,
    Horror,
    Music,
    Musical,
    Mystery,
    Romance,
    SciFi,
    Sport,
    Thriller,
    War,
    Western,
}

impl TryFrom<i32> for Genre {
    type Error = AppError;

    fn try_from(val: i32) -> Result<Self, AppError> {
        match val {
            1 => Ok(Self::Action),
            2 => Ok(Self::Adventure),
            3 => Ok(Self::Animation),
            4 => Ok(Self::Biography),
            5 => Ok(Self::Comedy),
            6 => Ok(Self::Crime),
            7 => Ok(Self::Documentary),
            8 => Ok(Self::Drama),
            9 => Ok(Self::Family),
            10 => Ok(Self::Fantasy),
            11 => Ok(Self::History),
            12 => Ok(Self::Horror),
            13 => Ok(Self::Music),
            14 => Ok(Self::Musical),
            15 => Ok(Self::Mystery),
            16 => Ok(Self::Romance),
            17 => Ok(Self::SciFi),
            18 => Ok(Self::Sport),
            19 => Ok(Self::Thriller),
            20 => Ok(Self::War),
            21 => Ok(Self::Western),
            _ => Err(AppError::UnmappedInputError(val, "Genre")),
        }
    }
}

pub fn validate<T: TryFrom<i32>>(val: u32) -> Result<i32, T::Error> {
    let i = val as i32;
    T::try_from(i).map(|_| i)
}
