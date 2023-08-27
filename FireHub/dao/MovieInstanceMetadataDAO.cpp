#include "MovieInstanceMetadataDAO.h"

#include "Database.h"
#include "LoggerHelper.h"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;

static string toSQLFieldValue(const string& str)
{
    return "'" + str + "'";
}

static string toSQLFieldValue(const string* str)
{
    return str == nullptr ? "NULL" : toSQLFieldValue(*str);
}

static string getTextField(sqlite3_stmt* stmt, int idx)
{
    assert(SQLITE3_TEXT == sqlite3_column_type(stmt, idx));
    return reinterpret_cast<const char*>(sqlite3_column_text(stmt, idx));
}

static string* getOptionalTextField(sqlite3_stmt* stmt, int idx)
{
    const int type = sqlite3_column_type(stmt, idx);
    switch (type) {
    case SQLITE3_TEXT:
        return new string(
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, idx)));
    case SQLITE_NULL:
        return nullptr;
    default:
        // Shouldn't happen
        assert(false);
    }
}

MovieInstanceMetadataDAO::MovieInstanceMetadataDAO(
    Database& dbHandle,
    Logger& logger)
    : dbHandle(dbHandle), log(logger)
{
}

int64_t MovieInstanceMetadataDAO::create(
    const string& title,
    const string* magnetLink,
    const string* coverImageLink)
{
    Transaction transaction = dbHandle.newTransaction();
    stringstream statement;
    statement << "INSERT INTO MOVIE_INSTANCE_METADATA"
              << "(TITLE, MAGNET_LINK, COVER_IMAGE_LINK) "
              << "VALUES (" << toSQLFieldValue(title) << ", "
              << toSQLFieldValue(magnetLink) << ", "
              << toSQLFieldValue(coverImageLink) << ");";
    transaction.exec(statement);
    return transaction.getInsertedID();
}

void MovieInstanceMetadataDAO::getById(int64_t id, const Receiver& receiver)
{
    stringstream query;
    query << "SELECT TITLE, MAGNET_LINK, COVER_IMAGE_LINK "
          << "FROM MOVIE_INSTANCE_METADATA "
          << "WHERE ID == " << id;
    Scan scan = dbHandle.newScan(query);
    scan.run([&receiver](sqlite3_stmt* stmt) {
        // Make sure we have the expected fields (title, magnet, image)
        assert(3 == sqlite3_column_count(stmt));
        // Extract values
        string titleStr = getTextField(stmt, 0);
        string* magnetLink = getOptionalTextField(stmt, 1);
        string* coverImageLink = getOptionalTextField(stmt, 2);
        receiver(titleStr, magnetLink, coverImageLink);
        // We only expect one unique row
        return Scan::Command::STOP;
    });
}