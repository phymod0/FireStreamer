#include "MovieInstanceMetadataDAO.h"

#include "Database.h"
#include "LoggerHelper.h"

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
    statement << "INSERT INTO MOVIE_INSTANCE_METADATA(TITLE, "
                 "MAGNET_LINK, COVER_IMAGE_LINK) VALUES ("
              << toSQLFieldValue(title) << ", " << toSQLFieldValue(magnetLink)
              << ", " << toSQLFieldValue(coverImageLink) << ");";
    transaction.exec(statement);
    return transaction.getInsertedID();
}