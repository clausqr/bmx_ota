#include <mutex>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ESPAsyncWebServer.h"

#include "bmx_logger.h"

#include "bmx_wifi.h"
// #include "bmx_webserial.h"
#include "bmx_ota.h"
#include "bmx_spiffs.h"
#include "bmx_webserver.h"
#include "bmx_servo.h"
#include "bmx_main.h"
#include "bmx_ros2.h"

// initialize logger

// Define the static member
BMX *BMX::instance = nullptr;


extern BMXLogger* logger;

BMX::BMX(const BMXConfig &config) : port(config.port),
                                    wifi_list((wifi_creds *)config.wifi_list),
                                    hostname(config.hostname),
                                    handler_count(0)
{

  {
    if (config.use_wifi)
    {
      Serial.println("Setting up WiFi"); // Debug print before setup_wifi()
      setup_wifi();
      Serial.println("WiFi setup complete"); // Debug print after setup_wifi()
    }

    // Initialize the logger
    logger = &BMXLogger::getInstance(config.logger_config);
    logger->log("BMX instance created");

    if (config.use_ota)
    {
      Serial.println("Setting up OTA"); // Debug print before setup_ota()
      setup_ota();
      Serial.println("OTA setup complete"); // Debug print after setup_ota()
    }
    if (config.use_webserver)
    {
      Serial.println("Setting up webserver"); // Debug print before setup_webserver()
      setup_webserver();
      Serial.println("Webserver setup complete"); // Debug print after setup_webserver()
    }
    if (config.use_webserial)
    {
      // logger->log("Setting up webserial"); // Debug print before setup_webserial()
      // setup_webserial();
      // logger->log("Webserial setup complete"); // Debug print after setup_webserial()
    }
    if (config.use_spiffs)
    {
      logger->log("Setting up SPIFFS"); // Debug print before setup_spiffs()
      setup_spiffs();
      logger->log("SPIFFS setup complete"); // Debug print after setup_spiffs()
    }
    if (config.use_esp32_servo)
    {
      logger->log("Setting up ESP32 Servo"); // Debug print before setup_servo()
      setup_servo(config.servo_pwm_update_timestep);
      logger->log("ESP32 Servo setup complete"); // Debug print after setup_servo()
    }
    if (config.use_ros2)
    {
      logger->log("Setting up ROS2"); // Debug print before setup_ros2()
      setup_ros2();
      logger->log("ROS2 setup complete"); // Debug print after setup_ros2()
    }
  }
}

BMX::~BMX()
{
}

void BMX::setup_wifi()
{
  // Start wifi
  bmx_wifi_connect_and_set_hostname_verbose(wifi_list, hostname);
}

void BMX::setup_ota()
{
  // Start OTA update service
  logger->log("Starting OTA update service"); // Debug print before starting OTA update service
  bmx_ota_start();
  logger->log("OTA update service started"); // Debug print after starting OTA update service
  // register the OTA handler with the main handler
  add_handler([]()
              { bmx_ota_handle(); });
  logger->log("OTA handler added"); // Debug print after adding OTA handler
}

void BMX::setup_webserver()
{
  // Start webserver
  this->server = new AsyncWebServer(port);
  bmx_webserver_setup(this->server);
  this->server->begin();
}

void BMX::setup_webserial()
{
  // Setup webserial interface (access via http://<ip>/webserial)
  // bmx_webserial_start(this->server);
}

void BMX::setup_spiffs()
{
  // Start SPIFFS
  bmx_spiffs_start();
}

void BMX::webprint(const char *msg)
{
  // bmx_webprint(msg);
}

void BMX::setup_servo(const unsigned int timestep)
{
  // bmx_servo_start();
  logger->log("Creating BMXServoHandler instance"); // Debug print before creating BMXServoHandler instance
  servo_handler = new BMXServoHandler(timestep);

  logger->log("BMXServoHandler instance created"); // Debug print after creating BMXServoHandler instance
  // register the servo handler with the main handler
  add_handler([this]()
              {
    if (this->servo_handler) {
      this->servo_handler->handle();
    } });
  logger->log("Servo handler added"); // Debug print after adding servo handler
}

void BMX::setup_ros2()
{
  // add handler for ROS2
  logger->log("Creating BMXROS2 instance"); // Debug print before creating BMXROS2 instance
  ros2 = new BMXROS2();
  logger->log("BMXROS2 instance created"); // Debug print after creating BMXROS2 instance
  add_handler([this]()
              { this->ros2->handle(); });
  logger->log("ROS2 handler added"); // Debug print after adding ROS2 handler
}

void BMX::add_handler(std::function<void()> handler)
{
  if (handler_count < MAX_HANDLERS)
  {
    handlers[handler_count++] = handler;
    Serial.print("Added handler ");
    logger->log(handler_count - 1);
  }
  else
  {
    // Handle error: max handlers reached
    // Optional: Log an error message or handle overflow
  }
  Serial.print("Handler count: ");
  logger->log(handler_count);
  logger->log("Handler added");
}

void BMX::remove_handler(std::function<void()> handler)
{
  // not implemented
  // for (int i = 0; i < handlers.size(); i++)
  // {
  //   if (handlers[i] == handler)
  //   {
  //     handlers.erase(handlers.begin() + i);
  //   }
  // }
}

void BMX::handle()
{

  Serial.print("Executing ROS2 handler ");
  Serial.print(0);
  Serial.print(" at time ");
  logger->log(millis());

  this->ros2->handle();
  bmx_ota_handle();

  Serial.print("Handler ");
  Serial.print(0);
  Serial.print(" ended execution at time ");
  Serial.print(millis());
  logger->log("OK");
  logger->log("Handled all");
}
