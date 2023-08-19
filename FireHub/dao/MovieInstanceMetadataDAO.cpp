#include "MovieInstanceMetadataDAO.h"

MovieInstanceMetadataDAO::MovieInstanceMetadataDAO(
    Database& dbHandle,
    const Logger& logger)
    : db(dbHandle), log(logger)
{
}
