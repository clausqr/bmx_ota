#include <Arduino.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"


#include <WebSerial.h>

#include "bmx_webserial.h"

void bmx_webserial_recvMsg_test(uint8_t *data, size_t len)
{
  WebSerial.println("Received Data...");
  String d = "";
  for (int i = 0; i < len; i++)
  {
    d += char(data[i]);
  }
  WebSerial.println(d);

}

void bmx_webserial_start(AsyncWebServer* server)
{
    WebSerial.begin(server);
    WebSerial.msgCallback(bmx_webserial_recvMsg_test);
}
  

void bmx_webprint(String s)
{
    WebSerial.println(s);
}