#include "BXCommandMode.h"

/* Functions declarations */
void CMD_PIDValues(); 
void CMD_TestMotors();
void CMD_SwitchPID(); 
void CMD_SetLPFAlpha(); 
void CMD_SetOffsets(); 
void CMD_StartAccelOffsets(); 
void CMD_StartGyroOffsets(); 
void CMD_MotorsSwitch(); 
void CMD_SetMotorOffset(); 
void CMD_StopMotors();

void CMD_init(){    
}
                          
void CMD_shortCutCommands(uint8_t infoByte){
  
    switch(infoByte & COMMAND_SHORTCUT_MASK){
       case SHRTCMD_TESTMOTORS: CMD_TestMotors(); break;
       case SHRTCMD_STOPMOTORS: CMD_StopMotors(); break;
    }
}

void CMD_TestMotors(){
           
}

void CMD_StopMotors(){
           COMM_flush();
           MMD_setMotorSpeed( 1, 0 );
           MMD_setMotorSpeed( 2, 0 );
           TM_pendMotorSpeed();
}

