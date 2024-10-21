
#include <Arduino.h>
#include <WiFiUdp.h>
#include <Syslog.h>

#include "bmx_main.h"
#include "bmx_logger.h"

// Create a global Syslog instance
WiFiUDP udpClient;
Syslog syslog(udpClient, SYSLOG_PROTO_IETF);


// Initialize static members
std::unique_ptr<BMXLogger> BMXLogger::instance;
std::once_flag BMXLogger::initFlag;

// Global reference to BMXLogger
BMXLogger* logger = nullptr;

// Static method to get the singleton instance with parameters
BMXLogger &BMXLogger::getInstance(const BMXLoggerConfig &config)
{
    std::call_once(initFlag, [&]()
                   { instance.reset(new BMXLogger(config)); });
    return *instance;
}

// Static method to get the singleton instance without parameters
BMXLogger &BMXLogger::getInstance()
{
    if (!instance)
    {
        throw std::runtime_error("BMXLogger is not initialized. Call getInstance with BMXLoggerConfig first.");
    }
    return *instance;
}
BMXLogger::BMXLogger() : config_({{}, LogLevel::NONE})
{
    // Default constructor
}

BMXLogger::BMXLogger(const BMXLogger::BMXLoggerConfig &config) : config_(config)
{
    // Initialize Serial logging if SERIALLOG is configured and Serial is not already initialized
    if (std::find(config_.log_types.begin(), config_.log_types.end(), BMXLogger::LogType::BMX_LOG_SERIAL) != config_.log_types.end())
    {
        if (!Serial)
        {
            Serial.begin(config_.serial.baud_rate);
            while (!Serial)
            {
                // Wait for Serial port to connect (only needed for native USB)
            }
        }
    }

    // Initialize Syslog if SYSLOG is configured
    if (std::find(config_.log_types.begin(), config_.log_types.end(), BMXLogger::LogType::BMX_LOG_SYSLOG) != config_.log_types.end())
    {
        syslog.server(config_.syslog.server.c_str(), config_.syslog.port);
        syslog.deviceHostname(config_.syslog.hostname.c_str());
        syslog.appName(config_.syslog.tag.c_str());
    }
}

void BMXLogger::log(const char *message)
{
    log(config_.default_level, message);
}

void BMXLogger::log(const int number)
{
    char buffer[10];
    itoa(number, buffer, 10);
    log(config_.default_level, buffer);
}

void BMXLogger::log(BMXLogger::LogLevel level, const char *message)
{
    if (level < config_.min_level)
    {
        return; // Do not log if the level is below the minimum level
    }

    // Log to Serial if configured
    if (std::find(config_.log_types.begin(), config_.log_types.end(), BMX_LOG_SERIAL) != config_.log_types.end())
    {
        logSerial(level, message);
    }

    // Log to Syslog if configured
    if (std::find(config_.log_types.begin(), config_.log_types.end(), BMX_LOG_SYSLOG) != config_.log_types.end())
    {
        logSyslog(level, message);
    }
}

void BMXLogger::logSerial(BMXLogger::LogLevel level, const char *message)
{
    if (!Serial)
    {
        return; // Return if Serial is not initialized
    }

    Serial.print("[");
    Serial.print(logLevelToString(level));
    Serial.print("] ");
    Serial.println(message);
}

void BMXLogger::logSyslog(BMXLogger::LogLevel level, const char *message)
{
    syslog.log(convertLogLevelToSyslog(level), message);
}

int BMXLogger::convertLogLevelToSyslog(BMXLogger::LogLevel level)
{
    switch (level)
    {
    case DEBUG:
        return LOG_DEBUG;
    case INFO:
        return LOG_INFO;
    case WARN:
        return LOG_WARNING;
    case ERROR:
        return LOG_ERR;
    case FATAL:
        return LOG_CRIT;
    default:
        return LOG_NOTICE;
    }
}

const char *BMXLogger::logLevelToString(BMXLogger::LogLevel level)
{
    switch (level)
    {
    case NONE:
        return "NONE";
    case DEBUG:
        return "DEBUG";
    case INFO:
        return "INFO";
    case WARN:
        return "WARN";
    case ERROR:
        return "ERROR";
    case FATAL:
        return "FATAL";
    default:
        return "UNKNOWN";
    }
}
