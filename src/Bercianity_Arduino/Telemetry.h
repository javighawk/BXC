#ifndef Telemetry_h
#define Telemetry_h

/*****************************************/
/**************** INCLUDES ***************/
/*****************************************/

#include "BXC.h"
#include "BXCOMM.h"
#include "BXMoveMode.h"
#include "TimeRecord.h"
#include "TimeOut.h"


/*****************************************/
/**************** DEFINES ****************/
/*****************************************/

#define TELEMETRY         0x0E
#define TM_PETITION       0x0F
#define TEL_SPEED         0x00
#define TEL_BYTEINFO      0x02
#define TEL_TIMEOUT       0x03
#define TEL_ACCEL         0x06
#define TEL_DIFFMOTOR     0x09
#define TEL_PIDVALUES     0x0A
#define TEL_ALPHA_ACCEL   0x0B
#define TEL_ACCELOFFSETS  0x0C
#define TEL_GYRO          0x0D
#define TEL_ALPHA_GYRO    0x10
#define TEL_ALPHA_DEG     0x11
#define TEL_GYROOFFSETS   0x12
#define TEL_MOTORSPOWER   0x13
#define TEL_MOTOROFFSETS  0x14
#define TEL_TIMES         0x17
#define TEL_TIMELABELS    0x18
#define ENDOFTM           0x05

#define TELEMETRYTIME       40


/*****************************************/
/************** FUNCTIONS ****************/
/*****************************************/

void TM_start();
void TM_checkTelemetry();
void TM_pendMotorSpeed();
void TM_pendTimeLabels();
void TM_cancel();

#endif
