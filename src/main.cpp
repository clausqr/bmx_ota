#include <Arduino.h>

#include "secrets.h"

#include "bmx_config.h"
#include "bmx_main.h"


#define HOSTNAME "bmx21"

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
  bmx->handle();

  float yaw = 0.0f;
  float pitch = 0.0f;
  float roll = 0.0f;
  char buf[2048];
  const char *fmt = "{\"yaw\":%f, \"pitch\":%f, \"roll\":%f}";
  snprintf(buf, sizeof(buf), fmt, yaw, pitch, roll);
  bmx->webprint(buf);

  delay(500);
}