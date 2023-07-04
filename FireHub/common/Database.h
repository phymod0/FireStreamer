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
    void begin();
    void exec(const std::string&);
    void end();
    Database(const std::string&);
    ~Database();
};

#endif /* DATABASE */
