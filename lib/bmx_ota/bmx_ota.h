#ifndef BMX_OTA
#define BMX_OTA

#if defined(BMX_USE_OTA) && (BMX_USE_OTA == true)

#include <Arduino.h>
#include <WiFi.h>

void bmx_ota_start();

void bmx_ota_handle();

#endif /* BMX_USE_OTA */
#endif /* BMX_OTA */
