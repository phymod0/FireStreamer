#ifndef MOVIE_INSTANCE_METADATA_DAO
#define MOVIE_INSTANCE_METADATA_DAO

#include "BaseApplication.h"
#include "Database.h"
#include "LoggerHelper.h"

#include <sqlite3.h>

#include <cstdint>
#include <functional>
#include <string>

using std::function;
using std::string;

class BaseApplication;

class MovieInstanceMetadataDAO
{
    Database& dbHandle;
    const Logger& log;
    friend BaseApplication;
    MovieInstanceMetadataDAO(Database&, Logger&);
    using Receiver =
        function<void(const string&, const string*, const string*)>;

public:
    int64_t create(const string&, const string*, const string*);
    void getById(int64_t, const Receiver& receiver);
};

#endif /* MOVIE_INSTANCE_METADATA_DAO */
