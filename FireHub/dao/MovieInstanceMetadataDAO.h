#ifndef MOVIE_INSTANCE_METADATA_DAO
#define MOVIE_INSTANCE_METADATA_DAO

#include "Database.h"
#include "LoggerHelper.h"

#include <sqlite3.h>

#include <cstdint>
#include <string>

using std::string;

class MovieInstanceMetadataDAO
{
    Database& dbHandle;
    const Logger& log;

public:
    // TODO(phymod0): Make SoapServer a factory for DAO instances instead
    MovieInstanceMetadataDAO(Database&, const Logger&);
    int64_t create(const string&, const string*, const string*);
};

#endif /* MOVIE_INSTANCE_METADATA_DAO */
