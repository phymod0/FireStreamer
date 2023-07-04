#include <stdexcept>
#include <string>

#include "CommonConstants.h"
#include "Database.h"
#include "LoggerHelper.h"

#include <sqlite3.h>

using std::runtime_error;
using std::string;

static const Logger LOG = LoggerHelper::getBootstrapLogger(__FILE__);

static void logAndThrow(const string& errorMessage)
{
    LOG->error(errorMessage);
    throw runtime_error(errorMessage);
}

sqlite3* Database::get()
{
    return db;
}

void Database::begin()
{
    char* errMsg;
    const int rc = sqlite3_exec(
        db,
        Constants::DatabaseCommands::BEGIN_TRANSACTION,
        NULL,
        NULL,
        &errMsg);
    if (rc != SQLITE_OK) {
        const string error =
            "BEGIN transaction failed due to error: " + string(errMsg);
        sqlite3_free(errMsg);
        logAndThrow(error);
    }
}

void Database::exec(const string& sqlStr)
{
    char* errMsg;
    const int rc = sqlite3_exec(db, sqlStr.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        const string error = "Failed to execute statement [" + sqlStr +
                             "] due to error: " + string(errMsg);
        sqlite3_free(errMsg);
        logAndThrow(error);
    }
}

void Database::end()
{
    char* errMsg;
    const int rc = sqlite3_exec(
        db,
        Constants::DatabaseCommands::END_TRANSACTION,
        NULL,
        NULL,
        &errMsg);
    if (rc != SQLITE_OK) {
        const string error =
            "END transaction failed due to error: " + string(errMsg);
        sqlite3_free(errMsg);
        logAndThrow(error);
    }
}

Database::Database(const string& dbPath)
{
    sqlite3* db;
    const int rc = sqlite3_open(dbPath.c_str(), &db);
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
