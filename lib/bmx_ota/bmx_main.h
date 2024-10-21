#ifndef BMX_MAIN
#define BMX_MAIN

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ESPAsyncWebServer.h"

#include <cstddef> // for std::size_t

#include "bmx_wifi.h"
#include "bmx_logger.h"

#define MAX_HANDLERS 32 // Adjust the size as needed

struct BMXConfig {
  const wifi_creds *wifi_list;
  const char *hostname;
  uint16_t port;
  bool use_wifi;
  bool use_ota;
  bool use_webserver;
  bool use_webserial;
  bool use_spiffs;
  bool use_esp32_servo;
  bool use_ros2;
  bool use_logging;
  uint16_t servo_pwm_update_timestep;
  BMXLogger::BMXLoggerConfig logger_config;
};


class BMXServoHandler;
class BMXROS2;
class BMX
{

public:
  BMX(const BMXConfig& config);
  ~BMX();

  static BMX* instance;


  void setup();
  void handle();

  void webprint(const char *msg);

  void add_handler(std::function<void()> handler);
  void remove_handler(std::function<void()> handler);

private:
  uint16_t port;
  AsyncWebServer *server;
  wifi_creds *wifi_list; // Defined in bmx_wifi.h
  const char *hostname;        // Defined in bmx_wifi.h
  void setup_wifi();
  void setup_ota();
  void setup_webserver();
  void setup_webserial();
  void setup_spiffs();
  void setup_servo(const unsigned int timestep);
  void setup_ros2();



  BMXServoHandler *servo_handler;
  
  std::array<std::function<void()>, MAX_HANDLERS> handlers;
  std::size_t handler_count;
  
  BMX(); // Constructor to initialize handler_count

  BMXROS2 *ros2;

};

#endif /* BMX_MAIN */
