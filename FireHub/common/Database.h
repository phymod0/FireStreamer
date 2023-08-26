/*
 * Wrappers for automatic lifecycle management.
 */
#ifndef DATABASE
#define DATABASE

#include "LoggerHelper.h"

#include <sqlite3.h>

#include <cstdint>
#include <functional>
#include <sstream>
#include <string>

using std::function;
using std::string;
using std::stringstream;

class Transaction;
class Scan;

class Database
{
    sqlite3* db;
    const Logger& log;
    void logAndThrow(const string&);
    void doExecWithoutParams(const string&);

public:
    Database(const string&, const Logger&);
    Database(const Database&) = delete;
    void exec(const string&);
    Transaction newTransaction();
    Scan newScan(const string& query);
    Scan newScan(const stringstream& query);
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
    void exec(const string&);
    void exec(const stringstream&);
    uint64_t getInsertedID();
    ~Transaction();
};

class Scan
{
    sqlite3* db;
    const Logger& log;
    sqlite3_stmt* stmt;
    friend Scan Database::newScan(const string&);
    friend Scan Database::newScan(const stringstream&);
    void logAndThrow(const string&);
    Scan(sqlite3*, const Logger&, const string);

public:
    using Command = enum { CONTINUE, STOP };
    using StatementReceiver = function<Command(sqlite3_stmt*)>;
    Scan(const Scan&) = delete;
    sqlite3* getDbPtr();
    void run(const StatementReceiver&);
    ~Scan();
};

#endif /* DATABASE */
