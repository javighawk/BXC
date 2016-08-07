#include "BXCOMM.h"
#include "BXMoveMode.h"
#include "TimeOut.h"
#include "Telemetry.h"
#include "BXCommandMode.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "TimeRecord.h"
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include <Wire.h>
#include <NXTI2CDevice.h>
#include <NXTMMX.h>

/* Time record objects */
TimeRecord tLoop("LOOP");
TimeRecord tInfoRead("READ");
TimeRecord tAvailable("AVAIL");
TimeRecord tConnected("CNNCT");
TimeRecord tTelemetry("TM");


/*
 * Setup function
 */
void setup(){
    // Setup Serial (not needed for COMM with server)
    Serial.begin(SERIAL_BPS);

    // Setup LEDs
    pinMode(GREENLEDPIN,OUTPUT);
    pinMode(REDLEDPIN,OUTPUT);
    pinMode(SERIALPIN,OUTPUT);
    digitalWrite(GREENLEDPIN, LOW);
    digitalWrite(REDLEDPIN, LOW);
    digitalWrite(SERIALPIN, LOW);
    
    // Setup modules
    MVM_init();
    CMD_init();
    COMM_init();

    // Update timeout
    TMO_feed();
}


/*
 * Loop function
 */
void loop(){

    // Start loop time recording
    tLoop.TIME_trigger();

    // Check Telemetry send
    TM_checkTelemetry();

    // Check Time Out
    if( TMO_checkTimeOut() );

    // Read incoming data if available
    int data = COMM_read();

    // Check if we received data
    if( data > 0 ){
        // Check for telemetry confirmation
        if( data == TM_CONFIRMATION ){
          tTelemetry.TIME_trigger();
          TM_start();
          tTelemetry.TIME_stop();
        }

        else{
            switch(data & MODE_MASK){
                // Move mode
                case MOVE_MODE:
                case SPIN_MODE:
                    MVM_run(data);
                    break;

                // Command mode
                case COMMAND_MODE:
                    CMD_run(data);
                    break
            }
        }
    }
      
    }

    // Stop loop time recording
    tLoop.TIME_stop();
}
