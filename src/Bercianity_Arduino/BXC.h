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

#define MOVE_MODE                 0x00
#define SPIN_MODE                 0x0C
#define COMMAND_MODE              0x08

#define MODE_MASK                 0x0C
#define SPEED_MASK                0x03
#define DIRECTION_MASK            0x30


/*********************************************************/
/********************* PIN DEFINES ***********************/
/*********************************************************/

#define MOTOR1_PIN                3
#define MOTOR2_PIN                4
#define MOTOR3_PIN                5
#define MOTOR4_PIN                6
#define SETUPLED_PIN              10
#define COMMLED_PIN               11
#define CONNECTIONLED_PIN         12
#define IMU_INTERRUPTPIN          17


/*********************************************************/
/********************* LED DEFINES ***********************/
/*********************************************************/

#define REDLED_PIN                SETUPLED_PIN
#define GREENLED_PIN              COMMLED_PIN
#define BLUELED_PIN               CONNECTIONLED_PIN


/*********************************************************/
/******************** OTHER DEFINES **********************/
/*********************************************************/

#define SERIAL_BPS                115200
#define ON                        1
#define OFF                       0

#endif
