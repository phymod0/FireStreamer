/*
 * Wrappers for automatic lifecycle management.
 */

#ifndef DATABASE
#define DATABASE

#include <map>
#include <string>

#include <sqlite3.h>

class Transaction;

class Database
{
    sqlite3* db;

public:
    Database(const std::string&);
    void exec(const std::string&);
    Transaction newTransaction();
    ~Database();
};

class Transaction
{
    sqlite3* db;
    friend Transaction Database::newTransaction();
    Transaction(sqlite3* db);

public:
    sqlite3* getDbPtr();
    void exec(const std::string&);
    ~Transaction();
};

#endif /* DATABASE */
