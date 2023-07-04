#include <string>
#include <vector>

#include "Configuration.h"
#include "Database.h"
#include "LoggerHelper.h"

class SoapServer
{
private:
    const std::string& serverName;

protected:
    Logger logger;
    Database dbHandle;

public:
    Logger getLogger() const;
    Database getDBHandle() const;
    void run();
    SoapServer(
        const std::string& serverName,
        const Configuration& configuration);
};

class ApplicationServer : public SoapServer
{
private:
    static const std::string SERVER_NAME;
    static const std::vector<std::string> tableDefinitions;

    void initialize();

public:
    ApplicationServer(const Configuration& configuration);
};
