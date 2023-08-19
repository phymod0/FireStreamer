#ifndef MOVIE_INSTANCE_METADATA_DAO
#define MOVIE_INSTANCE_METADATA_DAO

#include "Database.h"
#include "LoggerHelper.h"

#include <sqlite3.h>

#include <map>
#include <string>

class MovieInstanceMetadataDAO
{
    Database& db;
    const Logger& log;

public:
    MovieInstanceMetadataDAO(Database& dbHandle, const Logger& log);
};

#endif /* MOVIE_INSTANCE_METADATA_DAO */
