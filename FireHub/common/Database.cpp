#include <stdexcept>
#include <string>

#include "Database.h"
#include "LoggerHelper.h"

#include <sqlite3.h>

using std::runtime_error;
using std::string;

static const Logger LOG = LoggerHelper::getBootstrapLogger(__FILE__);

static inline void logAndThrow(const string& errorMessage)
{
    LOG->error(errorMessage);
    throw runtime_error(errorMessage);
}

sqlite3* Database::get()
{
    return db;
}

void Database::exec(const string& sqlStr)
{
    char* errorMsg;
    int rc = sqlite3_exec(db, sqlStr.c_str(), nullptr, nullptr, &errorMsg);
    if (rc != SQLITE_OK) {
        const string error = "Failed to execute statement [" + sqlStr +
                             "] due to error: " + errorMsg;
        sqlite3_free(errorMsg);
        logAndThrow(error);
    }
}

Database::Database(const string& dbPath)
{
    sqlite3* db;
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        const string error = "Failed to open database at path " + dbPath +
                             " due to error: " + sqlite3_errmsg(db);
        sqlite3_close(db);
        logAndThrow(error);
    }
    this->db = db;
    LOG->debug("Opened database at path {}", dbPath);
}

Database::~Database()
{
    int rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        LOG->warn("Failed to close database: {}", sqlite3_errmsg(db));
    }
}