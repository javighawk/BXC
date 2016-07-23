#include "Telemetry.h"

/* Auxiliar variable to measure Telemetry period */
unsigned long timer;

/* Auxiliary variables */
boolean pendingTM = false;

/* Other TM Pending Boolean Variables */
boolean pendingMotorSpeedTM = true;
boolean pendingTimeLabelsTM = true;

/* Extern variables */
extern TimeRecord tLoop;
extern TimeRecord tInfoRead;
extern TimeRecord tTelemetry;
extern TimeRecord tInfoRead;
extern TimeRecord tAvailable;
extern TimeRecord tConnected;


/*
 * Notifies the end of Telemetry transmission
 */
void TM_end(){
    COMM_write( ENDOFTM );
    COMM_flush();
    pendingTM = false;
}
    

void TM_motorsSpeedTelemetry(){
    
    /* Motors speed */
    int mSpeed[2] = {MMD_getMotorSpeed(1),
                     MMD_getMotorSpeed(2)};
    uint8_t header[3] = {sizeof(mSpeed[0]), sizeof(mSpeed)/sizeof(mSpeed[0]), TEL_SPEED};
    
    // Send Motors speed
    COMM_write( header, 3 );
    for( int i=0 ; i<header[1] ; i++ )
        COMM_write( (uint8_t*)&mSpeed[i], header[0] );
}
  
  
void TM_timeTelemetry(){

    unsigned long times[6] = {millis(),
                              tLoop.TIME_getAvgTime(),
                              tTelemetry.TIME_getAvgTime(),
                              tConnected.TIME_getAvgTime(),
                              tAvailable.TIME_getAvgTime(),
                              tInfoRead.TIME_getAvgTime()};
    
    uint8_t header[3] = {sizeof(times[0]), sizeof(times)/sizeof(times[0]), TEL_TIMES};
    COMM_write( header, 3 );
    COMM_write( (uint8_t*)&times[0], header[0] );
    COMM_write( (uint8_t*)&times[1], header[0] );
    COMM_write( (uint8_t*)&times[2], header[0] );
    COMM_write( (uint8_t*)&times[3], header[0] );
    COMM_write( (uint8_t*)&times[4], header[0] );
    COMM_write( (uint8_t*)&times[5], header[0] );

    // Reset the records
    tLoop.TIME_resetMaxTRec();
    tInfoRead.TIME_resetMaxTRec();
    tTelemetry.TIME_resetMaxTRec();
}

void TM_timeLabelsTelemetry(){
  
    char labels[5][LABEL_LENGTH];
    String labels_str[5] = {tLoop.TIME_getLabel(),
                            tTelemetry.TIME_getLabel(),
                            tConnected.TIME_getLabel(),
                            tAvailable.TIME_getLabel(),
                            tInfoRead.TIME_getLabel()};

    for( int i=0 ; i<LABEL_LENGTH ; i++ )
        for( int j=0 ; j<5 ; j++ )
            if( i < labels_str[0].length() ) labels[j][i] = labels_str[j][i];
            else labels[j][i] = 0;

    uint8_t header[3] = {sizeof(labels[0]), sizeof(labels)/sizeof(labels[0]), TEL_TIMELABELS};
    COMM_write( header, 3 );
    COMM_write( (uint8_t*)labels[0], header[0] );
    COMM_write( (uint8_t*)labels[1], header[0] );
    COMM_write( (uint8_t*)labels[2], header[0] );
    COMM_write( (uint8_t*)labels[3], header[0] );
    COMM_write( (uint8_t*)labels[4], header[0] );
  
}

void TM_start(){  

    if( pendingTM ){
        COMM_write( TELEMETRY );
        
        TM_timeTelemetry();
        
        if( pendingMotorSpeedTM ){
            TM_motorsSpeedTelemetry();
            pendingMotorSpeedTM = false;
        }
        if( pendingTimeLabelsTM ){
            TM_timeLabelsTelemetry();
            pendingTimeLabelsTM = false;
        }
        
        TM_end();      
    }
}
  
void TM_checkTelemetry(){
  
    if( (!pendingTM) && ((millis() - timer) >= TELEMETRYTIME) ){
        timer = millis();
        COMM_write( TM_PETITION );
        COMM_flush();
        pendingTM = true;
    }    
}

void TM_pendMotorSpeed(){ pendingMotorSpeedTM = true; }
void TM_pendTimeLabels(){ pendingMotorSpeedTM = true; }
void TM_cancel(){ pendingTM = false; }
