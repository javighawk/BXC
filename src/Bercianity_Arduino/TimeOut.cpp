#include "TimeOut.h"

/* Last time TimeOut was refreshed */
unsigned long currentTime;


/*
 * Update the timing variable
 */
void TMO_feed(){
    currentTime = millis();
}


/*
 * Perform Time out checking operation
 * 
 * @return 1 if connection has timed out. 0 otherwise.
 */
int TMO_checkTimeOut(){
    // Check if connection has timed out
    if( (millis() - currentTime) < TIMEOUT_EXPIRED )
        return 0;

    // Close COMM socket
    COMM_closeSocket();

    // Stop bot
    MMD_stopBot();

    // Reset all LED indicators
    digitalWrite(SETUPLED_PIN, LOW);
    digitalWrite(WIFICONNLED_PIN, LOW);
    digitalWrite(CONNECTIONLED_PIN, LOW);

    // Perform COMM initialization again
    COMM_init();    

    // Reset the time out counter
    currentTime = millis();

    // Cancel any telemetry petition
    TM_cancel();

    // Set pending all TM
    TM_pendMotorSpeed();
    TM_pendTimeLabels();
    
    return 1;    
}
