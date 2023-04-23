#ifndef DATABASE
#define DATABASE

#include <map>
#include <string>

#include <sqlite3.h>

/*
 * Wrapper for automatic lifecycle management.
 */
class Database
{
    sqlite3* db;

public:
    sqlite3* get();
    void exec(const std::string&);
    Database(const std::string&);
    ~Database();
};

#endif /* DATABASE */