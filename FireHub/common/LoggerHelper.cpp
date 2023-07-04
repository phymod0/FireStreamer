#include <iostream>

#include "LoggerHelper.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define SEPARATOR               "::"
#define LOGGER_PREFIX           "Logger" SEPARATOR
#define BOOTSTRAP_LOGGER_PREFIX "BootstrapLogger" SEPARATOR

using std::string;

Logger LoggerHelper::getLogger(
    const string& name,
    const Configuration& configuration)
{
    const string loggerName = LOGGER_PREFIX + name;
    const Logger existingLogger = spdlog::get(loggerName);
    if (existingLogger != nullptr) {
        return existingLogger;
    }
    const string logFileDir = configuration.getLogFolder();
    const string logFileName = configuration.getLogName();
    const string logFilePath = logFileDir + "/" + logFileName + ".log";
    return spdlog::basic_logger_mt(loggerName, logFilePath);
}

Logger LoggerHelper::getBootstrapLogger(const string& name)
{
    const string loggerName = BOOTSTRAP_LOGGER_PREFIX + name;
    const Logger existingLogger = spdlog::get(loggerName);
    if (existingLogger != nullptr) {
        return existingLogger;
    }
    return spdlog::stdout_color_mt(loggerName);
}
