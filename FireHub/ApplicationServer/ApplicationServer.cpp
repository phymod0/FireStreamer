#include <iostream>
#include <string>
#include <vector>

#include "ApplicationServer.h"
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

const string ApplicationServer::SERVER_NAME = "ApplicationServer";

const vector<string> ApplicationServer::tableDefinitions = {
    Constants::TableDefinitions::MOVIE_INSTANCE_METADATA,
};

void ApplicationServer::initialize()
{
    for (const string& tableDefinition : tableDefinitions) {
        const string createTableQuery =
            "CREATE TABLE IF NOT EXISTS " + tableDefinition + ";";
        dbHandle.exec(createTableQuery);
    }
    logger->info("Tables initialized");
}

ApplicationServer::ApplicationServer(const Configuration& configuration)
    : BaseApplication(SERVER_NAME, configuration)
{
    initialize();
}

int main()
{
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
