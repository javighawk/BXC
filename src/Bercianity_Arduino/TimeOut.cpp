#include "TimeOut.h"

/* Last time TimeOut was refreshed */
unsigned long currentTime;

/*
 * Updates the timing variable
 */
void TMO_feed(){
    currentTime = millis();
}

/*
 * Performs Time out checking operation
 * 
 * @return 1 if connection has timed out. 0 otherwise.
 */
int TMO_checkTimeOut(){

    /* Check if connection has timed out */
    if( (millis() - currentTime) < TIMEOUT_EXPIRED )
        return 0;

    /* Close COMM socket */
    COMM_closeSocket();

    /* Stop bot */
    MMD_moveBot( 0, 0);

    /* Reset all LED indicators */
    digitalWrite(GREENLEDPIN, LOW);
    digitalWrite(REDLEDPIN, LOW);
    digitalWrite(SERIALPIN, LOW);

    /* Perform COMM initialization again */
    COMM_init();    

    /* Reset the time out counter */
    currentTime = millis();

    /* Cancel any telemetry petition */
    TM_cancel();
    
    return 1;    
}

/*
 * Getter
 */
unsigned long TMO_getCurrentTimeOut(){
    return (millis() - currentTime);
}
