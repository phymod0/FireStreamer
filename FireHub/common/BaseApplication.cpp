#include "BaseApplication.h"
#include "Configuration.h"
#include "Database.h"
#include "LoggerHelper.h"
#include "MovieInstanceMetadataDAO.h"

#include "soap/soapH.h"

#include <string>

using std::string;

static const Logger LOG = LoggerHelper::getBootstrapLogger(__FILE__);

Logger BaseApplication::getLogger() const
{
    return logger;
}

Database& BaseApplication::getDBHandle()
{
    return dbHandle;
}

void BaseApplication::run()
{
    struct soap* soap = soap_new();
    soap->user = this;
    soap_serve(soap);
}

BaseApplication::BaseApplication(
    const string& serverName,
    const Configuration& configuration)
    : serverName(serverName),
      logger(LoggerHelper::getLogger(serverName, configuration)),
      dbHandle(configuration.getDatabasePath(), logger)
{
}

MovieInstanceMetadataDAO BaseApplication::getMovieInstanceMetadataDAO()
{
    return MovieInstanceMetadataDAO(dbHandle, logger);
}