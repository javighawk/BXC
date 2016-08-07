#ifndef BXMoveMode_h
#define BXMoveMode_h

/*****************************************/
/**************** INCLUDES ***************/
/*****************************************/

#include "BXC.h"
#include "TimeOut.h"
#include "Telemetry.h"
#include <Wire.h>
#include <NXTI2CDevice.h>
#include <NXTMMX.h>


/*****************************************/
/**************** DEFINES ****************/
/*****************************************/

#define MAX_SPEED     100



/*****************************************/
/************** FUNCTIONS ****************/
/*****************************************/

void MVM_init();
void MVM_run(int infoByte);
int MVM_getMotorSpeed( int motor );
void MVM_moveBot(byte speedT, byte direction);
void MVM_moveDiagonalBot(byte speedT, byte direction);
void MVM_setMotorSpeed( int motor, int speed );
void MVM_setMotorOffset( byte mot, byte sp );
byte MVM_getMotorOffset( int mot );

#endif
