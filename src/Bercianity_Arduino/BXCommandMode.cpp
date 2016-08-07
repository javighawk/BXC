#include "BXCommandMode.h"


/*
 * Test motors
 */
void CMD_TestMotors(){
    // Get motor
    int m = COMM_read_wTimeOut();

    // Move motor for half a second in one direction
    MVM_setMotorSpeed(m, MAX_SPEED);
    delay(500);

    // Move motor for half a second in the other direction
    MVM_setMotorSpeed(m, -MAX_SPEED);
    delay(500);

    // Stop motor
    MVM_setMotorSpeed(m, 0);
}


/*
 * Run command mode. Execeute incoming command
 */
void CMD_run(){
    // Read command
    int command = COMM_read_wTimeOut();

    // Run
    switch(command){
       case CMD_TESTMOTORS: CMD_TestMotors(); break;
    }
}
