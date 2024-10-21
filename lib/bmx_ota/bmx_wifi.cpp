#include <Arduino.h>
#include <WiFi.h>

#include <bmx_wifi.h>
#include <ESP32Ping.h>
#include <ESPmDNS.h>

bool bmx_wifi_connect(const wifi_creds *wifi_list)
{
    // scan for nearby networks:
    byte numSsid = WiFi.scanNetworks();

    // best rssi for search
    int best_rssi = -999;
    int theNet = -1;
    int theNet_from_our_list = -1;

    // print the network number and name for each network found:
    for (int thisNet = 0; thisNet < numSsid; thisNet++)
    {

        int thatNet = 0;
        while (wifi_list[thatNet].SSID != "")
        {
            if (WiFi.SSID(thisNet) == wifi_list[thatNet].SSID)
            {
                if (WiFi.RSSI(thisNet) > best_rssi)
                {
                    best_rssi = WiFi.RSSI(thisNet);
                    theNet = thisNet;
                    theNet_from_our_list = thatNet;
                }
            }
            thatNet++;
        }
    }

    if (theNet == -1)
    {
        return false;
    }
    else
    {

        auto conn_try = 0;

        WiFi.mode(WIFI_STA);
        delay(10);

        while ((WiFi.status() != WL_CONNECTED) && (conn_try < WIFI_CONN_RETRIES))
        {
            WiFi.begin(wifi_list[theNet_from_our_list].SSID,
                       wifi_list[theNet_from_our_list].pass);

            int conn_time = 0;

            while ((WiFi.status() != WL_CONNECTED) && (conn_time++ < WIFI_CONN_TIMEOUT))
            {
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }

            if (WiFi.status() == WL_CONNECTED)
            {
                return true;
            }

            conn_try++;
        }
    }
    return (WiFi.status() == WL_CONNECTED);
}

void bmx_wifi_connect_verbose(const struct wifi_creds *wifi_list)
{
    Serial.print("Connecting to WiFi... ");
    if (bmx_wifi_connect(wifi_list))
    {
        Serial.println("OK!");
    }
    else
    {
        Serial.println("ERROR");
    }

    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void bmx_wifi_connect_and_set_hostname_verbose(const wifi_creds *wifi_list, const char *hostname)
{
    WiFi.setHostname(hostname);

    Serial.print("Connecting to WiFi... ");
    if (bmx_wifi_connect(wifi_list))
    {
        Serial.println("OK!");
    }
    else
    {
        Serial.println("ERROR");
    }

    // Initialize mDNS
    if (!MDNS.begin(hostname))
    { // Set the hostname
        Serial.println("Error setting up MDNS responder!");
        while (1)
        {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");

    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
