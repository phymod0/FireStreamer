#include <iostream>
#include <string>
#include <vector>

#include "ApplicationServerConstants.h"
#include "CommonConstants.h"
#include "Configuration.h"
#include "Database.h"
#include "LoggerHelper.h"
#include "soap/soapH.h"

#include <jsoncpp/json/json.h>
#include <spdlog/cfg/env.h>
#include <spdlog/spdlog.h>
#include <sqlite3.h>

using namespace std;
using namespace spdlog;

static const Logger LOG = LoggerHelper::getBootstrapLogger(__FILE__);

class SoapServer
{
private:
    const string& serverName;

protected:
    virtual void initialize() = 0;
    virtual void validate() = 0;

public:
    void run()
    {
        soap_serve(soap_new());
    }

    SoapServer(const string& serverName, const Configuration& configuration)
        : serverName(serverName)
    {
    }
};

class ApplicationServer : public SoapServer
{
    static inline const string SERVER_NAME = "ApplicationServer";
    static inline const vector<string> tableDefinitions = {
        Constants::TableDefinitions::MOVIE_INSTANCE_METADATA,
    };
    const Logger logger;
    Database dbHandle;

public:
    void validate()
    {
        logger->info("Validations successful!");
    }

    void initialize()
    {
        for (const string& tableDefinition : tableDefinitions) {
            const string createTableQuery =
                "CREATE TABLE IF NOT EXISTS " + tableDefinition + ";";
            dbHandle.exec(createTableQuery);
        }
        logger->info("Tables initialized");
    }

    ApplicationServer(const Configuration& configuration)
        : SoapServer(SERVER_NAME, configuration),
          logger(LoggerHelper::getLogger(SERVER_NAME, configuration)),
          dbHandle(configuration.getDatabasePath())
    {
        validate();
        initialize();
    }
};

int main()
{
    // TODO(phymod0): Get from arguments otherwise
    // decide defaults
    spdlog::cfg::load_env_levels();
    try {
        const Configuration configuration =
            Configuration::loadFromFile(Constants::CONFIG_PATH);
        ApplicationServer(configuration).run();
    } catch (const runtime_error& e) {
        LOG->error("Failed to initialize application server: {}", e.what());
        return 1;
    }
    return 0;
}