#ifndef CONFIGURATION
#define CONFIGURATION

#include <string>

#include <jsoncpp/json/json.h>

class Configuration
{
    const Json::Value configurationJson;
    Configuration(const Json::Value);

public:
    static Configuration loadFromFile(const std::string&);
    std::string getLogFolder() const;
    std::string getLogName() const;
    std::string getDatabasePath() const;
};

#endif /* CONFIGURATION */