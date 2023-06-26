#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ESPAsyncWebServer.h"

#include "bmx_wifi.h"

#include "secrets.h"

#include "bmx_webserial.h"
#include "bmx_ota.h"
#include "bmx_spiffs.h"
#include "bmx_webserver.h"


#define LED LED_BUILTIN
#define HOSTNAME "bmx21"

class BMX
{

public : 
  BMX();
  BMX(uint16_t port);
  ~BMX();

  void setup();
  void loop();

private:
  uint16_t port;
  AsyncWebServer* server;
  void setup_wifi();
  void setup_ota();
  void setup_webserver();
  void setup_webserial();
  void setup_spiffs();
};

#define BMX_USE_WIFI true
#define BMX_USE_OTA true
#define BMX_USE_WEBSERVER true
#define BMX_USE_WEBSERIAL true
#define BMX_USE_SPIFFS true

BMX::BMX(uint16_t port)
{
  this->port = port;
  if (BMX_USE_WIFI)
  {
    setup_wifi();
  }
  if (BMX_USE_OTA)
  {
    setup_ota();
  }
  if (BMX_USE_WEBSERVER)
  {
    setup_webserver();
  }
  if (BMX_USE_WEBSERIAL)
  {
    setup_webserial();
  }
  if (BMX_USE_SPIFFS)
  {
    setup_spiffs();
  }
}

BMX::~BMX()
{
}

void BMX::setup_wifi()
{
  // Start wifi
  bmx_wifi_connect_and_set_hostname_verbose(wifi_list, HOSTNAME);
}

void BMX::setup_ota()
{
  // Start OTA update service
  bmx_ota_start();
}

void BMX::setup_webserver()
{
  // Start webserver
  this->server = new AsyncWebServer(port);
  this->server->begin();
}

void BMX::setup_webserial()
{
  // Setup webserial interface (access via http://<ip>/webserial)
  bmx_webserial_start(this->server);
}

void BMX::setup_spiffs()
{
  // Start SPIFFS
  bmx_spiffs_start();
}



BMX* bmx;

void setup()
{
  // Start serial ...
  Serial.begin(115200);
  Serial.println("Booting");

  bmx = new BMX(80);

}

void loop()
{
  bmx_ota_handle();

  float yaw = 0.0f;
  float pitch = 0.0f;
  float roll = 0.0f;
  char buf[2048];
  const char *fmt = "{\"yaw\":%f, \"pitch\":%f, \"roll\":%f}";
  snprintf(buf, sizeof(buf), fmt, yaw, pitch, roll);
  bmx_webprint(buf);

  delay(500);
}