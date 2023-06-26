#ifndef BMX_MAIN
#define BMX_MAIN

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ESPAsyncWebServer.h"

class BMX
{

public : 
  BMX();
  BMX(const wifi_creds* wifi_list, const char* hostname, uint16_t port);
  ~BMX();

  void setup();
  void handle();
  
  void webprint(const char* msg);


private:
  uint16_t port;
  AsyncWebServer* server;
  wifi_creds* wifi_list; //Defined in bmx_wifi.h
  char* hostname; //Defined in bmx_wifi.h
  void setup_wifi();
  void setup_ota();
  void setup_webserver();
  void setup_webserial();
  void setup_spiffs();
};

#endif /* BMX_MAIN */
