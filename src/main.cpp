#include <Arduino.h>

#define BMX_USE_WIFI true
#define BMX_USE_OTA true
#define BMX_USE_WEBSERVER true
#define BMX_USE_WEBSERIAL true
#define BMX_USE_SPIFFS true

#include "secrets.h"


#define LED LED_BUILTIN
#define HOSTNAME "bmx21"

#include "bmx_main.h"

BMX* bmx;

void setup()
{
  // Start serial ...
  Serial.begin(115200);
  Serial.println("Booting");

  bmx = new BMX(wifi_list, HOSTNAME, 80);

}

void loop()
{
  //bmx_ota_handle();

  float yaw = 0.0f;
  float pitch = 0.0f;
  float roll = 0.0f;
  char buf[2048];
  const char *fmt = "{\"yaw\":%f, \"pitch\":%f, \"roll\":%f}";
  snprintf(buf, sizeof(buf), fmt, yaw, pitch, roll);
  bmx->webprint(buf);

  delay(500);
}