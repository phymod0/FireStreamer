#ifndef MOVIE_INSTANCE_METADATA_DAO
#define MOVIE_INSTANCE_METADATA_DAO

#include "BaseApplication.h"
#include "Database.h"
#include "LoggerHelper.h"

#include <sqlite3.h>

#include <cstdint>
#include <string>

using std::string;

class BaseApplication;

class MovieInstanceMetadataDAO
{
    Database& dbHandle;
    const Logger& log;
    friend BaseApplication;
    // TODO(phymod0): Make SoapServer a factory for DAO instances instead
    MovieInstanceMetadataDAO(Database&, Logger&);

public:
    int64_t create(const string&, const string*, const string*);
};

#endif /* MOVIE_INSTANCE_METADATA_DAO */
