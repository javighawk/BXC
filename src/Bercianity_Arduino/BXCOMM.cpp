#include "BXCOMM.h"
#include "TimeOut.h"
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>

/* WiFi handler */
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIV2);

/* Client */
Adafruit_CC3000_Client clientTCP;

/* Server IP address */
uint32_t serverIP = cc3000.IP2U32(192, 168, 0, 230);

/* Server ports */
int serverPort_TCP = 4444;

/* Transmission buffer */
uint8_t buf[BUFFER_SIZE];

/* Transmission buffer index */
int buf_index = 0;

/* External declarations */
extern TimeRecord tInfoRead;
extern TimeRecord tAvailable;
extern TimeRecord tConnected;


/*
 * Initializing function
 */
void COMM_init(){

    // Initialize WiFi board
    if ( !cc3000.begin() ){
        
        // An error occured
        while( 1 ){
            digitalWrite(SETUPLED_PIN, HIGH);
            delay(1000);
            digitalWrite(SETUPLED_PIN, LOW);
            delay(1000);
        }
    }

    // Turn on LED indicator
    digitalWrite(SETUPLED_PIN, HIGH);

    // Connect to WiFi network
    if ( !cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY) ){
        
        // Could not connect to the WiFi network
        while( 1 ){
            digitalWrite(WIFICONNLED_PIN, HIGH);
            delay(1000);
            digitalWrite(WIFICONNLED_PIN, LOW);
            delay(1000);
        }
    }

    // Connection successful. Turn on LED indicator
    digitalWrite(WIFICONNLED_PIN, HIGH);

    // Request DHCP
    while ( !cc3000.checkDHCP() ){
        delay(100);
    } 

    // Print through Serial the server IP address
    cc3000.printIPdotsRev(serverIP);
    Serial.println();

    // Connect to server
    while( 1 ){
        clientTCP = cc3000.connectTCP(serverIP, serverPort_TCP);

        // Check connection
        if( clientTCP.connected() ){
            Serial.println("Connected!");
            break;
        } else {
            // Blink twice
            digitalWrite(CONNECTIONLED_PIN, HIGH); delay(100);
            digitalWrite(CONNECTIONLED_PIN, LOW); delay(100);
            digitalWrite(CONNECTIONLED_PIN, HIGH); delay(100);
            digitalWrite(CONNECTIONLED_PIN, LOW); delay(100);

            // Close socket before retrying
            COMM_closeSocket();
            Serial.println("Connection to server failed");
        }
    }  

    // Turn on LED indicator
    digitalWrite(CONNECTIONLED_PIN, HIGH);
}


/*
 * Writes a character to the output buffer
 */
void COMM_write(uint8_t c, bool byteStuffing){
    COMM_write(&c, 1, byteStuffing);
}


/*
 * Writes an array of characters to the output buffer
 */
void COMM_write(uint8_t *c, int len, bool byteStuffing){

    for( int i=len-1 ; i>=0 ; i-- ){
        byte sending = *(c + i);

        // Send the whole buffer if full
        if( buf_index >= BUFFER_SIZE )
            COMM_flush();

        // Perform byte stuffing
        if( sending == ESC && byteStuffing ){
            buf[buf_index++] = ESC;
        }
        
        buf[buf_index++] = sending;
    }
}


/*
 * Cleans output buffer
 */
void COMM_cleanBuffer(){
    memset( buf, 0, BUFFER_SIZE );
    buf_index = 0;
}


/*
 * Flushes out output buffer
 */
void COMM_flush(){
    clientTCP.write(buf, buf_index);
    COMM_cleanBuffer();
}


/*
 * Read a character from input buffer. Checks if the connection 
 * times out while waiting for new data in the input buffer.
 */
int COMM_read_wTimeOut(){
    int c;
    while( (c = COMM_read()) == -1 )
        if( TMO_checkTimeOut() )
            return -1;

    return c;
}


/*
 * Reads a character from input buffer if available
 * If buffer is empty or it's disconnected, returns -1.
 */
int COMM_read(){
    tConnected.trigger();
    if( clientTCP.connected() ){
        tConnected.stop();
        tAvailable.trigger();
        if( clientTCP.available() ){
            tAvailable.stop();
            tInfoRead.trigger();
            int cs = clientTCP.read();
            tInfoRead.stop();
            TMO_feed();
            return cs;
        }
    }
    return -1;
}


/*
 * Disconnects WiFi board
 */
void COMM_disconnect(){
    cc3000.disconnect();
}


/*
 * Closes TCP socket
 */
void COMM_closeSocket(){
    clientTCP.close();
}
