#ifndef BMX_CONFIG
#define BMX_CONFIG

#include "bmx_main.h"

// Configure BMX features
#define BMX_USE_OTA true

// Configure WiFi
#define BMX_USE_WIFI true
#include "secrets.h"     // WiFi credentials
#define HOSTNAME "bmx21" // hostname to use for mDNS
// WiFi Services
#define BMX_USE_WEBSERVER false
#define BMX_USE_WEBSERIAL false

// SPIFFS
#define BMX_USE_SPIFFS true

// Servo
#define BMX_ESP32_SERVO false
#define SERVO_PWM_UPDATE_TIMESTEP 100
#include "bmx_servo_config.h"

// ROS2
#define BMX_USE_ROS2 true
#include "bmx_ros2_config.h"

// Logging
#define BMX_USE_LOGGING true
#include "bmx_logger.h"

#define BMX_LOG_SYSLOG_SERVER "192.168.0.114"
#define BMX_LOG_SYSLOG_PORT 514
#define BMX_LOG_SYSLOG_HOSTNAME "ESP32"
#define BMX_LOG_SYSLOG_APPNAME "bmx_ota"
#define BMX_LOG_SYSLOG_TAG "BMX"

BMXLogger::BMXLoggerConfig logger_config = 
{
    .log_types = 
    {
        BMXLogger::LogType::BMX_LOG_SERIAL,
        BMXLogger::LogType::BMX_LOG_SYSLOG
    },
    .default_level = BMXLogger::LogLevel::INFO,
    .min_level = BMXLogger::LogLevel::INFO,
    .serial = 
    {
        .baud_rate = 115200
    },
    .syslog = 
    {
        .server = BMX_LOG_SYSLOG_SERVER,
        .port = BMX_LOG_SYSLOG_PORT,
        .tag = BMX_LOG_SYSLOG_TAG,
        .hostname = BMX_LOG_SYSLOG_HOSTNAME
    }
};

// Condense into a single configuration struct
BMXConfig default_config = 
{
    .wifi_list = wifi_list,
    .hostname = HOSTNAME,
    .port = 80,
    .use_wifi = BMX_USE_WIFI,
    .use_ota = BMX_USE_OTA,
    .use_webserver = BMX_USE_WEBSERVER,
    .use_webserial = BMX_USE_WEBSERIAL,
    .use_spiffs = BMX_USE_SPIFFS,
    .use_esp32_servo = BMX_ESP32_SERVO,
    .use_ros2 = BMX_USE_ROS2,
    .use_logging = BMX_USE_LOGGING,
    .servo_pwm_update_timestep = SERVO_PWM_UPDATE_TIMESTEP,
    .logger_config = logger_config
};

#endif /* BMX_CONFIG */
