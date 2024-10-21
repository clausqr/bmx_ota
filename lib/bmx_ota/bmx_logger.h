#ifndef BMXLOGGER_H
#define BMXLOGGER_H

#include <vector>
#include <string>
#include <mutex>

class BMXLogger
{
public:

    // Enum declarations are correct
    enum LogLevel
    {
        NONE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    enum LogType
    {
        BMX_LOG_SERIAL,
        BMX_LOG_SYSLOG
    };

    struct BMXLoggerConfig
    {
        std::vector<LogType> log_types;
        LogLevel default_level;
        LogLevel min_level;

        struct SerialConfig
        {
            long baud_rate;
            // Default constructor for SerialConfig
            SerialConfig(long rate = 115200) : baud_rate(rate) {}
        } serial;

        struct SyslogConfig
        {
            std::string server;
            uint16_t port;
            std::string tag;
            std::string hostname;

            // Default constructor for SyslogConfig
            SyslogConfig(
                const std::string &srv = "",
                uint16_t p = 514,
                const std::string &tg = "BMX",
                const std::string &host = "ESP32")
                : server(srv),
                  port(p),
                  tag(tg),
                  hostname(host)
            {
            }
        } syslog;

        // Default constructor for BMXLoggerConfig
        BMXLoggerConfig(
            std::vector<LogType> types = {BMX_LOG_SERIAL},
            LogLevel level = NONE,
            LogLevel minLevel = NONE,
            SerialConfig sconfig = SerialConfig(),
            SyslogConfig scfg = SyslogConfig()) : log_types(types),
                                                  default_level(level),
                                                  min_level(minLevel),
                                                  serial(sconfig),
                                                  syslog(scfg)
        {
        }
    };


    static BMXLogger &getInstance();
    static BMXLogger &getInstance(const BMXLoggerConfig &config);

    // Log function
    void log(LogLevel level, const char *message);
    void log(const char *message);
    void log(const int number);


    // delete copy constructor and assignment operator for singleton pattern
    BMXLogger(BMXLogger const &) = delete;
    void operator=(BMXLogger const &) = delete;

  

private:
    // Default constructor: Private because of singleton pattern
    BMXLogger();
    // Constructor for specifying log types and level: Private because of singleton pattern
    BMXLogger(const BMXLoggerConfig &config);

    BMXLoggerConfig config_;

    // Private logging functions
    void logSerial(BMXLogger::LogLevel level, const char *message);
    void logSyslog(BMXLogger::LogLevel level, const char *message);

    int convertLogLevelToSyslog(BMXLogger::LogLevel level);
    const char *logLevelToString(BMXLogger::LogLevel level);

        // Static instance pointer and initialization flag
    static std::unique_ptr<BMXLogger> instance;
    static std::once_flag initFlag;
};

#endif // BMXLOGGER_H
