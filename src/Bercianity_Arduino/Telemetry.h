#ifndef Telemetry_h
#define Telemetry_h

/*****************************************/
/**************** INCLUDES ***************/
/*****************************************/

#include "BXC.h"


/*****************************************/
/**************** DEFINES ****************/
/*****************************************/

#define TEL_SPEED         0x00
#define TEL_TIMES         0x17
#define TEL_TIMELABELS    0x18
#define TELEMETRYTIME       20


/*****************************************/
/************** FUNCTIONS ****************/
/*****************************************/

void TM_start();
void TM_checkTelemetry();
void TM_pendMotorSpeed();
void TM_pendTimeLabels();
void TM_cancel();

#endif
