/*******************************************
 *  _ _                      _ _ 
 * | 4 |                    | 1 |
 * |_ _|                    |_ _|                          
 *     \\                  //
 *      \\                //
 *       \\              //
 *        \\            //
 *         \\__________//
 *         |  BX_Drone  |
 *         | __________ |
 *         //          \\
 *        //            \\
 *       //              \\
 *      //                \\
 *  _ _//                  \\_ _ 
 * | 3 |                    | 2 |
 * |_ _|                    |_ _|
 * 
 *******************************************/

#include "BXMoveMode.h"

/* NTXMMX object */
NXTMMX mmx;

/* Total current speed */
int totalSpeed = 0;

/* Motors speed */
int mSpeed[2] = {0, 0};

/* Motors speed offset */
byte mOffset[2] = {0, 0};

void MVM_init(){
    mmx.reset();
}

void MVM_run(int infoByte){
  
    uint8_t speedInfo = infoByte & SPEED_MASK;
    uint8_t directionInfo = infoByte & DIRECTION_MASK;
    uint8_t modeInfo = infoByte & MODE_MASK;
    int totalSpeed;

    if( speedInfo == 0x01 ){ 
        if( (totalSpeed = COMM_read_wTimeOut()) == -1 ) return;
        Serial.println(totalSpeed);
    }
    else if( speedInfo == 0x02 ) totalSpeed = 0;
    
    if( modeInfo == 0 ) MVM_moveBot(totalSpeed, directionInfo);
    else if( modeInfo == 12 ) MVM_moveDiagonalBot(totalSpeed, directionInfo);
}

/*
 * Moves the bot forwards, backwards or spin around itself
 */
void MVM_moveBot(byte speedT, byte direction){

    switch(direction){
    case 0x00:
        MVM_setMotorSpeed( 1, speedT );
        MVM_setMotorSpeed( 2, speedT );
        break;
  
    case 0x10:
        MVM_setMotorSpeed( 1, -speedT );
        MVM_setMotorSpeed( 2, -speedT );
        break;
  
    case 0x20:
        MVM_setMotorSpeed( 1, -speedT );
        MVM_setMotorSpeed( 2, speedT );
        break;
  
    case 0x30: 
        MVM_setMotorSpeed( 1, speedT );
        MVM_setMotorSpeed( 2, -speedT );
        break;
    }
    
    TM_pendMotorSpeed();
}


/* 
 * Moves bot in a circle
 */
void MVM_moveDiagonalBot(byte speedT, byte direction){

    switch(direction){
    case 0x00: 
        MVM_setMotorSpeed( 2, (int) speedT/2 );
        MVM_setMotorSpeed( 1, speedT );
        break;
    case 0x10: 
        MVM_setMotorSpeed( 2, (int)-speedT/2 );
        MVM_setMotorSpeed( 1, -speedT );
        break;
    case 0x20:
        MVM_setMotorSpeed( 1, (int)speedT/2 );
        MVM_setMotorSpeed( 2, speedT );
        break;
    case 0x30:
        MVM_setMotorSpeed( 1, (int)-speedT/2 );
        MVM_setMotorSpeed( 2, -speedT );
        break;
    }
    
    TM_pendMotorSpeed();
}


void MVM_setMotorSpeed( int motor, int speed ){

    int dir = MMX_Direction_Forward;
  
    if( motor < 1 || motor > 2 ) return;

    mSpeed[motor-1] = speed;
  
    if( speed < 0 ){
        speed = -speed;
        dir = MMX_Direction_Reverse;
    }
    
    if( speed > MAX_SPEED ) speed = MAX_SPEED;
  
    switch(motor){
        case 1:
          mmx.runUnlimited(MMX_Motor_1, dir, speed);
          break;
      
        case 2:
          mmx.runUnlimited(MMX_Motor_2, dir, speed);
          break;
    }   
}


int MVM_getMotorSpeed( int motor ){ return mSpeed[motor-1]; }
void MVM_setMotorOffset( byte mot, byte sp ){ mOffset[mot-1] = sp; }
byte MVM_getMotorOffset( int mot ){ return mOffset[mot-1]; }
