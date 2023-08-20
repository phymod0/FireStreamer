#include "Database.h"
#include "CommonConstants.h"
#include "LoggerHelper.h"

#include <sqlite3.h>

#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;
using std::stringstream;

static void __logAndThrow(const string& errorMessage, const Logger& log)
{
    log->error(errorMessage);
    throw runtime_error(errorMessage);
}

static void __doExecWithoutParams(
    const string& sqlStr,
    sqlite3* db,
    const Logger& log)
{
    char* errMsg;
    log->debug("Executing statement: " + sqlStr);
    const int rc = sqlite3_exec(db, sqlStr.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        const string error = "Failed to execute statement [" + sqlStr +
                             "] due to error: " + string(errMsg);
        sqlite3_free(errMsg);
        __logAndThrow(error, log);
    }
}

static uint64_t getLastInsertedID(sqlite3* db)
{
    return sqlite3_last_insert_rowid(db);
}

void Database::logAndThrow(const string& errorMessage)
{
    __logAndThrow(errorMessage, log);
}

void Database::doExecWithoutParams(const string& sqlStr)
{
    __doExecWithoutParams(sqlStr, db, log);
}

void Transaction::logAndThrow(const string& errorMessage)
{
    __logAndThrow(errorMessage, log);
}

void Transaction::doExecWithoutParams(const string& sqlStr)
{
    __doExecWithoutParams(sqlStr, db, log);
}

Database::Database(const string& dbPath, const Logger& logger) : log(logger)
{
    sqlite3* db;
    log->debug("Opening database at path {}...", dbPath);
    const int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        const string error = "Failed to open database at path " + dbPath +
                             " due to error: " + sqlite3_errmsg(db);
        sqlite3_close(db);
        logAndThrow(error);
    }
    this->db = db;
    log->debug("Opened database at path {}", dbPath);
}

void Database::exec(const string& sqlStr)
{
    doExecWithoutParams(sqlStr);
}

Transaction Database::newTransaction()
{
    return Transaction(db, log);
}

Database::~Database()
{
    log->debug("Closing database...");
    int rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        log->warn("Failed to close database: {}", sqlite3_errmsg(db));
    }
}

Transaction::Transaction(sqlite3* db, const Logger& logger)
    : db(db), log(logger)
{
    char* errMsg;
    log->debug("Starting BEGIN transaction");
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

sqlite3* Transaction::getDbPtr()
{
    return db;
}

void Transaction::exec(const string& sqlStr)
{
    doExecWithoutParams(sqlStr);
}

void Transaction::exec(const stringstream& sqlStrStream)
{
    exec(sqlStrStream.str());
}

uint64_t Transaction::getInsertedID()
{
    return getLastInsertedID(db);
}

Transaction::~Transaction()
{
    char* errMsg;
    log->debug("Starting END transaction");
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