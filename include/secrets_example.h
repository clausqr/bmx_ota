#ifndef SECRETS_EXAMPLE
#define SECRETS_EXAMPLE
#ifndef SECRETS_EXAMPLE
#define SECRETS_EXAMPLE
#ifndef SECRETS
#define SECRETS

#include <Arduino.h>
#include "bmx_wifi.h"

// rename to secrets.h

struct wifi_creds; //Defined in bmx_wifi.h

const wifi_creds wifi_list[] = 
{
    // replace SSID_n and PASSWORD_n with actual SSIDs and passwords!
    {"SSID_1", "PASSWORD_1"}, 
    {"SSID_2", "PASSWORD_2"},
    {"SSID_3", "PASSWORD_3"},
    {"SSID_4", "PASSWORD_4"},
    {"", ""},   // End list with empty strings for SSID and PASSWORD
};

#endif /* SECRETS */


#endif /* SECRETS_EXAMPLE */


#endif /* SECRETS_EXAMPLE */
