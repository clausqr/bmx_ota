#include <Arduino.h>
#include <SPIFFS.h>

void bmx_spiffs_start()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
}

void bmx_spiffs_dump_file(String fname)
{
    File file = SPIFFS.open(fname);
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.println("File Content:");
    while (file.available())
    {
        Serial.write(file.read());
    }
    file.close();
}