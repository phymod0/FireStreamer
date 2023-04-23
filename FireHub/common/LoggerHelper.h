#ifndef LOGGER_HELPER
#define LOGGER_HELPER

#include <memory>
#include <string>

#include "Configuration.h"

#include <spdlog/spdlog.h>

using Logger = std::shared_ptr<spdlog::logger>;

class LoggerHelper
{
public:
    static Logger getLogger(const std::string&, const Configuration&);
    static Logger getBootstrapLogger(const std::string&);
};

#endif /* LOGGER_HELPER */