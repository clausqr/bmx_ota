#ifndef BMX_WIFI
#define BMX_WIFI

#define WIFI_CONN_TIMEOUT 15
#define WIFI_CONN_RETRIES 3

#define DELAY_ON_CONN_ERROR_S 30
#define DELAY_FOR_PING 1
#define PING_HOST "www.google.com"

struct wifi_creds
{
    const char* SSID;
    const char* pass;
};

bool bmx_wifi_connect(const wifi_creds *wifi_list);
    
void bmx_wifi_connect_verbose(const wifi_creds *wifi_list);

void bmx_wifi_connect_and_set_hostname_verbose(const wifi_creds *wifi_list, const char *hostname);


#endif /* BMX_WIFI */
