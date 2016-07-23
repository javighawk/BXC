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

void MMD_init();
void MMD_run(int infoByte);
int MMD_getMotorSpeed( int motor );
void MMD_moveBot(byte speedT, byte direction);
void MMD_moveDiagonalBot(byte speedT, byte direction);
void MMD_setMotorSpeed( int motor, int speed );
void MMD_setMotorOffset( byte mot, byte sp );
byte MMD_getMotorOffset( int mot );

#endif
