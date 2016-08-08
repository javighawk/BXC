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

#define MAX_SPEED                 100
#define SPEED_MASK                0x03
#define DIRECTION_MASK            0x30
#define DIR_UP                    0x00
#define DIR_DOWN                  0x10
#define DIR_LEFT                  0x20
#define DIR_RIGHT                 0x30
#define SPIN_U_L                  0x00
#define SPIN_U_R                  0x10
#define SPIN_D_L                  0x20
#define SPIN_D_R                  0x30
#define SPEED_NOCHANGE            0x00
#define SPEED_NEWSPEED            0x01
#define SPEED_STOP                0x02
#define MOTOR_L                   0
#define MOTOR_R                   1


/*****************************************/
/************** FUNCTIONS ****************/
/*****************************************/

void MVM_init();
void MVM_run(int data);
void MVM_stopBot();
void MVM_testMotors();
int MVM_getMotorSpeed(int motor);

#endif
