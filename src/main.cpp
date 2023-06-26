#include <Arduino.h>

// WiFi credentials
#include "secrets.h"

// BMX Config and include
#include "bmx_config.h"
#include "bmx_main.h"

// hostname to use for mDNS
#define HOSTNAME "bmx21"

// Create a new BMX instance
BMX* bmx;


void setup()
{
  // Start serial ...
  Serial.begin(115200);
  Serial.println("Booting");

  // Start BMX
  bmx = new BMX(wifi_list, HOSTNAME, 80);
}

void loop()
{
  // Handle BMX
  bmx->handle();

  // main loop, implement your application here!

  // print something to the webserial interface under http://<hostname>.local/webserial
  bmx->webprint("Hello World!");
  
  // wait a bit
  delay(500);
}