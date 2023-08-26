#include "MovieInstanceMetadataDAO.h"

#include "Database.h"
#include "LoggerHelper.h"

#include <cassert>
#include <cstdint>
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

static string* optionalTextFieldToStr(sqlite3_stmt* stmt, int idx)
{
    const char* charPtr =
        reinterpret_cast<const char*>(sqlite3_column_text(stmt, idx));
    return charPtr == nullptr ? nullptr : new string(charPtr);
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
          << "WHERE ID EQUALS " << id;
    Scan scan = dbHandle.newScan(query);
    scan.run([&receiver](sqlite3_stmt* stmt) {
        // ID + 3 other fields = 4 columns
        assert(4 == sqlite3_column_count(stmt));
        // Get title
        assert(SQLITE3_TEXT == sqlite3_column_type(stmt, 1));
        const string titleStr =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        // Get magnet link
        assert(SQLITE3_TEXT == sqlite3_column_type(stmt, 2));
        const string* magnetLink = optionalTextFieldToStr(stmt, 2);
        // Get cover image link
        assert(SQLITE3_TEXT == sqlite3_column_type(stmt, 3));
        const string* coverImageLink = optionalTextFieldToStr(stmt, 3);
        // Receive values
        receiver(titleStr, magnetLink, coverImageLink);
        // Cleanup
        delete magnetLink;
        delete coverImageLink;
        // We only expect one unique row
        return Scan::Command::STOP;
    });
}