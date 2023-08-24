#ifndef BASE_APPLICATION
#define BASE_APPLICATION

#include "Configuration.h"
#include "Database.h"
#include "LoggerHelper.h"
#include "MovieInstanceMetadataDAO.h"

#include <string>

using std::string;

class MovieInstanceMetadataDAO;

class BaseApplication
{
private:
    const string& serverName;

protected:
    Logger logger;
    Database dbHandle;

public:
    Logger getLogger() const;
    Database& getDBHandle();
    void run();
    BaseApplication(
        const std::string& serverName,
        const Configuration& configuration);
    MovieInstanceMetadataDAO getMovieInstanceMetadataDAO();
};

#endif /* BASE_APPLICATION*/