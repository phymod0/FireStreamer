#include "Configuration.h"
#include "CommonConstants.h"
#include "LoggerHelper.h"
#include "Utils.h"

#include <jsoncpp/json/json.h>

#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>

using std::getenv;
using std::nullopt;
using std::optional;
using std::string;

static const Logger LOG = LoggerHelper::getBootstrapLogger(__FILE__);

optional<string> getEnvironmentVariable(const char* key)
{
    const char* value = getenv(key);
    if (value) {
        return {string(value)};
    } else {
        return nullopt;
    }
}

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

Configuration Configuration::loadFromFile(const char* fileName)
{
    return loadFromFile(string(fileName));
}

string Configuration::getLogFolder() const
{
    const string logFolder = Utils::getJsonString(
        this->configurationJson,
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
    const optional<string> dbPathOptional =
        getEnvironmentVariable(Constants::EnvironmentVariables::DB_PATH);
    if (dbPathOptional == nullopt) {
        // Not specified in the env vars, get the DB path from JSON config
        const string dbPath = Utils::getJsonString(
            this->configurationJson,
            {"database", "dbPath"});
        LOG->debug("Got database path from JSON config: {}", dbPath);
        return dbPath;
    } else {
        // Use the DB path specified via FIRESTREAMER_DB_PATH
        const string dbPath = dbPathOptional.value();
        LOG->info("Using custom database path at {}", dbPath);
        return dbPath;
    }
}

Configuration::Configuration(const Json::Value configurationJson)
    : configurationJson(configurationJson)
{
}
