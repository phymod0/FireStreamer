#include "MovieInstanceMetadataDAO.h"

#include "Database.h"
#include "LoggerHelper.h"

#include <cstdint>

using std::string;

MovieInstanceMetadataDAO::MovieInstanceMetadataDAO(
    Database& dbHandle,
    const Logger& logger)
    : dbHandle(dbHandle), log(logger)
{
}

int64_t MovieInstanceMetadataDAO::create(
    const string& title,
    const string* magnetLink,
    const string* coverImageLink)
{
    (void) title;
    (void) magnetLink;
    (void) coverImageLink;
    Transaction transaction = dbHandle.newTransaction();
    sqlite3* db = transaction.getDbPtr();
    // TODO(phymod0): Add logic to insert movie instance metadata
    (void) db;
    return 786;
}
