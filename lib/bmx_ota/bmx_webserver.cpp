#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "bmx_spiffs.h"

#include "bmx_webserial.h"

void bmx_webserver_setup(AsyncWebServer* server)
{
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html"); });

    server->on("/demo.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/demo.js", "text/javascript"); });

    server->on("/testmsg", HTTP_GET, [](AsyncWebServerRequest *request)
              { bmx_webprint("testmsg"); });

    // respond to GET requests on URL /heap
    server->on("/heap", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(ESP.getFreeHeap())); });
}