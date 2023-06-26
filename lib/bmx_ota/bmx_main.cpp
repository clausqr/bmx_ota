#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ESPAsyncWebServer.h"


#define BMX_USE_WIFI true
#define BMX_USE_OTA true
#define BMX_USE_WEBSERVER true
#define BMX_USE_WEBSERIAL true
#define BMX_USE_SPIFFS true


#include "bmx_wifi.h"
#include "bmx_webserial.h"
#include "bmx_ota.h"
#include "bmx_spiffs.h"
#include "bmx_webserver.h"

#include "bmx_main.h"

BMX::BMX(const wifi_creds* wifi_list, const char* hostname, uint16_t port)
{
  this->port = port;
  this->wifi_list = (wifi_creds*)wifi_list;
  this->hostname = (char*)hostname;
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
 bmx_wifi_connect_and_set_hostname_verbose(wifi_list, hostname);
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

void BMX::webprint(const char* msg)
{
  bmx_webprint(msg);
}

void BMX::handle()
{
  bmx_ota_handle();
}