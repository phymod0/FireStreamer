#include <cerrno>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

#include "Configuration.h"
#include "LoggerHelper.h"
#include "Utils.h"

#include <jsoncpp/json/json.h>

using std::string;

static const Logger LOG = LoggerHelper::getBootstrapLogger(__FILE__);

Configuration Configuration::loadFromFile(const string& fileName)
{
    Json::Value jsonConfig;
    LOG->info("Loading config from file {}", fileName);
    std::ifstream jsonInput(fileName);
    if (jsonInput.fail()) {
        LOG->error("Failed to open {}: {}", fileName, strerror(errno));
        throw std::system_error(errno, std::generic_category(), fileName);
    }
    jsonInput >> jsonConfig;
    return Configuration(jsonConfig);
}

string Configuration::getLogFolder() const
{
    const string logFolder = Utils::getJsonString(this->configurationJson,
                                                  {"logging", "logFolderPath"});
    LOG->debug("Got log folder from JSON config: {}", logFolder);
    return logFolder;
}

string Configuration::getLogName() const
{
    const string logName =
        Utils::getJsonString(this->configurationJson, {"logging", "logName"});
    LOG->debug("Got log name from JSON config: {}", logName);
    return logName;
}

string Configuration::getDatabasePath() const
{
    const string dbPath =
        Utils::getJsonString(this->configurationJson, {"database", "dbPath"});
    LOG->debug("Got database path from JSON config: {}", dbPath);
    return dbPath;
}

Configuration::Configuration(const Json::Value configurationJson)
    : configurationJson(configurationJson)
{
}