/*
 * Wrappers for automatic lifecycle management.
 */
#ifndef DATABASE
#define DATABASE

#include "LoggerHelper.h"

#include <sqlite3.h>

#include <cstdint>
#include <sstream>
#include <string>

using std::string;

class Transaction;

class Database
{
    sqlite3* db;
    const Logger& log;
    void logAndThrow(const string&);
    void doExecWithoutParams(const string&);

public:
    Database(const std::string&, const Logger&);
    Database(const Database&) = delete;
    void exec(const std::string&);
    Transaction newTransaction();
    ~Database();
};

class Transaction
{
    sqlite3* db;
    const Logger& log;
    friend Transaction Database::newTransaction();
    void logAndThrow(const string&);
    void doExecWithoutParams(const string&);
    Transaction(sqlite3*, const Logger&);

public:
    Transaction(const Transaction&) = delete;
    sqlite3* getDbPtr();
    void exec(const std::string&);
    void exec(const std::stringstream&);
    uint64_t getInsertedID();
    ~Transaction();
};

#endif /* DATABASE */
