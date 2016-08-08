#ifndef BXCOMM_h
#define BXCOMM_h


/*****************************************/
/**************** INCLUDES ***************/
/*****************************************/

#include "BXC.h"


/*****************************************/
/**************** DEFINES ****************/
/*****************************************/

#define WLAN_SSID             "WiFiSSID"
#define WLAN_PASS             "WiFiPASS"
#define WLAN_SECURITY         WLAN_SEC_WPA2

#define ADAFRUIT_CC3000_IRQ   3  
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

#define BUFFER_SIZE           100
		

/*******************************************/
/**************** FUNCTIONS ****************/
/*******************************************/

void COMM_init();
void COMM_write(uint8_t c, bool byteStuffing = true);
void COMM_write(uint8_t *c, int len, bool byteStuffing = true);
void COMM_write_UDP(uint8_t c);
void COMM_flush();
int COMM_read();
int COMM_read_wTimeOut();
void COMM_disconnect();
void COMM_closeSocket();


#endif
