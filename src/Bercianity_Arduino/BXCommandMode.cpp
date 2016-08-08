#include "BXCommandMode.h"


/*
 * Test motors
 */
void CMD_TestMotors(){
    // Test motors
    MVM_testMotors();
}


/*
 * Run command mode. Execeute incoming command
 */
void CMD_run(){
    // Read command
    int command = COMM_read_wTimeOut();

    // Run
    switch( command ){
       case CMD_TESTMOTORS: CMD_TestMotors(); break;
    }
}
