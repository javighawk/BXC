#ifndef BXC_h
#define BXC_h

/*********************************************************/
/********************* INCLUDES **************************/
/*********************************************************/

#include "Arduino.h"
#include "TimeRecord.h"


/*********************************************************/
/****************** COMM PACKAGE DEFINES *****************/
/*********************************************************/

#define ENDOFTM                   0x05
#define TELEMETRY                 0x0E
#define TM_PETITION               0x0F
#define ENDOFPCK                  0x88
#define ESC                       0x7E
#define TM_CONFIRMATION           0x80


/*****************************************************/
/****************** MODES DEFINES ********************/
/*****************************************************/

#define MODE_MASK                 0x0C
#define MOVE_MODE                 0x00
#define SPIN_MODE                 0x0C
#define COMMAND_MODE              0x08


/*********************************************************/
/********************* PIN DEFINES ***********************/
/*********************************************************/

#define SETUPLED_PIN              10
#define WIFICONNLED_PIN           11
#define CONNECTIONLED_PIN         12


/*********************************************************/
/********************* LED DEFINES ***********************/
/*********************************************************/

#define REDLED_PIN                SETUPLED_PIN
#define GREENLED_PIN              WIFICONN_PIN
#define BLUELED_PIN               CONNECTIONLED_PIN


/*********************************************************/
/******************** OTHER DEFINES **********************/
/*********************************************************/

#define SERIAL_BPS                115200
#define ON                        1
#define OFF                       0

#endif
