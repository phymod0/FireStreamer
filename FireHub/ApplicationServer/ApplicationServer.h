#include <string>
#include <vector>

#include "Configuration.h"
#include "Database.h"
#include "LoggerHelper.h"

// TODO(phymod0): Rebrand as an application helper with server functionality
class BaseApplication
{
private:
    const std::string& serverName;

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
};

class ApplicationServer : public BaseApplication
{
private:
    static const std::string SERVER_NAME;
    static const std::vector<std::string> tableDefinitions;

    void initialize();

public:
    ApplicationServer(const Configuration& configuration);
};
