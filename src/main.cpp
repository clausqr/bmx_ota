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

AsyncWebServer server(80);

#define LED LED_BUILTIN
#define HOSTNAME "bmx21"

void setup()
{
  // Start serial ...
  Serial.begin(115200);
  Serial.println("Booting");

  // Start wifi
  bmx_wifi_connect_and_set_hostname_verbose(wifi_list, HOSTNAME);

  // Start OTA update service
  bmx_ota_start();

  // Start SPIFFS
  bmx_spiffs_start();

  // Setup webserver
  bmx_webserver_setup(&server);

  // Setup webserial interface (access via http://<ip>/webserial)
  bmx_webserial_start(&server);

  // Start webserver
  server.begin();
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