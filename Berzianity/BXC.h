#ifndef BXC_h
#define BXC_h

/*********************************************************/
/********************* INCLUDES **************************/
/*********************************************************/

#include "Arduino.h"
#include "TimeRecord.h"


/*********************************************************/
/*************** COMM PACKAGE DEFINES ********************/
/*********************************************************/

#define ESC                  0x7E
#define TM_CONFIRMATION      0x80


/*********************************************************/
/****************** INFO BYTE DEFINES ********************/
/*********************************************************/

#define MODE_MASK            0x0C
#define SPEED_MASK           0x03
#define DIRECTION_MASK       0x30
#define MOVEMODE_ID          0x00
#define SPINMODE_ID          0x0C
#define TEXTMODE_ID          0x04
#define COMMANDMODE_ID       0x08


/*********************************************************/
/********************* LEDs DEFINES **********************/
/*********************************************************/

#define SERIALPIN                7
#define REDLEDPIN                13
#define GREENLEDPIN              2


/*********************************************************/
/******************** OTHER DEFINES **********************/
/*********************************************************/    

#define SERIAL_BPS          115200  

#endif