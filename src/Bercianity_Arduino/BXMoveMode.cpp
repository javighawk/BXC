#include "BXMoveMode.h"

/* NTXMMX object */
NXTMMX mmx;

/* Motors identifiers */
int mID[2] = {MMX_Motor_1, MMX_Motor_2};

/* Motors speed */
int mSpeed[2] = {0, 0};


/*
 * Initializing function
 */
void MVM_init(){
    mmx.reset();
}


/*
 * Set a motor to a certain speed
 * 
 * @param m The motor index (MOTOR_L or MOTOR_R)
 * @param sp The speed the motor is set to (0-100)
 */
void MVM_setMotorSpeed(int m, int sp){
    // Initial assert
    if( m != MOTOR_L && m != MOTOR_R ) return;

    // Get motor direction
    int dir = (speed >= 0) * MMX_Direction_Forward + 
              (speed < 0) * MMX_Direction_Reverse;

    // Keep speed within boundaries and store it
    mSpeed[m] = max(0, min(MAX_SPEED, abs(sp)));

    // Apply speed
    mmx.runUnlimited(mID[m], dir, sp); 
}


/*
 * Move bot forward, backwards, rotate left or right
 * 
 * @param sp The speed the motors will move at
 * @param dir The direction the bot is to move to
 */
void MVM_moveBot(int sp, uint8_t dir){
    // Move motors
    switch( dir ){
        case MOVE_UP:
            MVM_setMotorSpeed( MOTOR_L, sp );
            MVM_setMotorSpeed( MOTOR_R, sp );
            break;
        case MOVE_DOWN:
            MVM_setMotorSpeed( MOTOR_L, -sp );
            MVM_setMotorSpeed( MOTOR_R, -sp );
            break;
        case MOVE_LEFT:
            MVM_setMotorSpeed( MOTOR_L, -sp );
            MVM_setMotorSpeed( MOTOR_R, sp );
            break;
        case MOVE_RIGHT: 
            MVM_setMotorSpeed( MOTOR_L, sp );
            MVM_setMotorSpeed( MOTOR_R, -sp );
            break;
        }

    // Set motor speed telemetry pending
    TM_pendMotorSpeed();
}


/* 
 * Moves bot front-right, front-left, back-right or back-left
 * 
 * @param sp The speed the bot will move at
 * @param dir The direction the bot is to move to
 */
void MVM_spinBot(int sp, uint8_t dir){
    // Move motors
    switch( dir ){
        case SPIN_U_L: 
            MVM_setMotorSpeed( MOTOR_L, (int)sp/2 );
            MVM_setMotorSpeed( MOTOR_R, sp );
            break;
        case SPIN_U_R: 
            MVM_setMotorSpeed( MOTOR_L, sp );
            MVM_setMotorSpeed( MOTOR_R, (int)sp/2 );
            break;
        case SPIN_D_L:
            MVM_setMotorSpeed( MOTOR_L, (int)-sp/2 );
            MVM_setMotorSpeed( MOTOR_R, -sp );
            break;
        case SPIN_D_R:
            MVM_setMotorSpeed( MOTOR_L, -sp );
            MVM_setMotorSpeed( MOTOR_R, (int)-sp/2 );
            break;
    }

    // Set motor speed telemetry pending
    TM_pendMotorSpeed();
}


/*
 * Main function
 * 
 * @data The data received from server
 */
void MVM_run(int data){
    // Extract data
    uint8_t speedID = data & SPEED_MASK;
    uint8_t direction = data & DIRECTION_MASK;
    uint8_t mode = data & MODE_MASK;
    int sp;
    
    // Get speed
    switch( speedID ){
        case SPEED_NEWSPEED:
            sp = COMM_read_wTimeOut();
            if( sp == -1 ) return;
            break;
        case SPEED_STOP:
            sp = 0;
            break;
        default:
            return;
    }

    // Apply movement
    switch( mode ){
        case MOVE_MODE:
            MVM_moveBot(sp, direction);
            break;
        case SPIN_MODE:
            MVM_spinBot(sp, direction);
            break;
        default:
            return;
    }
}


/*
 * Stop all motors
 */
void MVM_stopBot(){
    // Stop all motors
    MVM_setMotorSpeed(MOTOR_L, 0);
    MVM_setMotorSpeed(MOTOR_R, 0);
}


/*
 * Test motors connection. 
 * Run each motor 0.5 seconds in both directions
 */
void MVM_testMotors(){
    // Check if motors are all stopped
    if( mSpeed[MOTOR_L] != 0 || mSpeed[MOTOR_R] != 0 )
        return;

    // Test motors
    MVM_setMotorSpeed(MOTOR_L, 100);
    delay(500);
    MVM_setMotorSpeed(MOTOR_L, -100);
    delay(500);
    MVM_setMotorSpeed(MOTOR_L, 0);
    MVM_setMotorSpeed(MOTOR_R, 100);
    delay(500);
    MVM_setMotorSpeed(MOTOR_R, -100);
    delay(500);
    MVM_setMotorSpeed(MOTOR_R, 0);
}


/*
 * Getters
 */
int MVM_getMotorSpeed(int m){ return mSpeed[m]; }
