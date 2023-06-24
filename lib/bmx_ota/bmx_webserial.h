#ifndef BMX_WEBSERIAL
#define BMX_WEBSERIAL

void bmx_webserial_recvMsg_test(uint8_t* data, size_t len);

void bmx_webserial_start(AsyncWebServer* server);

void bmx_webprint(String s);


#endif /* BMX_WEBSERIAL */
