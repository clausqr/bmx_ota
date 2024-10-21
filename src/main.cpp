#include <Arduino.h>
#include "bmx_config.h" // BMX Configuration
#include "bmx_main.h"   // BMX Main

// Create a new BMX instance
BMX *bmx;
extern BMXLogger* logger;

void setup()
{
  // Start serial ...
  Serial.begin(115200);
  Serial.println("Booting");

  // Start BMX
  bmx = new BMX(default_config); // default_config is defined in bmx_config.h

}

void loop()
{
  // Handle BMX
  bmx->handle();

  logger->log(BMXLogger::LogLevel::ERROR, "lemon apple pear");

  delay(500);
}