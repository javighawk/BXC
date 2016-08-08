#include "Telemetry.h"

/* Extern declarations */
int MAIN_getNAllTimeRecord();
TimeRecord **MAIN_getAllTimeRecord();
extern TimeRecord tTelemetry;

/* Auxiliar variable to measure Telemetry period */
unsigned long timer;

/* Auxiliary variables */
boolean pendingTM = false;

/* Other TM Pending Boolean Variables */
boolean pendingMotorSpeedTM = true;
boolean pendingTimeLabelsTM = true;
    

/*
 * Send motors user speed
 */
void TM_mSpeedTelemetry(){
    
    // Motors speed
    int mSpeed[2] = {MVM_getMotorSpeed(MOTOR_L),
                     MVM_getMotorSpeed(MOTOR_R)};

    // hEADER
    uint8_t header[3] = {sizeof(mSpeed[0]), sizeof(mSpeed)/sizeof(mSpeed[0]), TEL_SPEED};
    
    // Send Motors speed
    COMM_write( header, 3 );
    for( int i=0 ; i<header[1] ; i++ )
        COMM_write( (uint8_t*)&mSpeed[i], header[0] );
}


/*
 * Send time telemetry
 */
void TM_timeTelemetry(){
    // Get array of all TimeRecord pointers and how many
    TimeRecord **allTR = MAIN_getAllTimeRecord();
    int nAllTR = MAIN_getNAllTimeRecord();

    // Get current time
    unsigned long nowTime = millis();

    // Get average time of all TimeRecord objects
    unsigned long avgTimeRecord[nAllTR];
    for( int i=0 ; i<nAllTR ; i++ ){
        avgTimeRecord[i] = allTR[i]->getAvgTime();

        // Reset all maxTime for TimeRecord objects
        allTR[i]->resetMaxTRec();
    }

    // Prepare Header
    uint8_t header[3] = {sizeof(nowTime), (uint8_t)(nAllTR + 1), TEL_TIMES};
    
    // Send first the current time, and then all the TimeRecord average times
    COMM_write( header, 3 );
    COMM_write( (uint8_t*)&nowTime, header[0] );
    for( int i=0 ; i<nAllTR ; i++ )
        COMM_write( (uint8_t*)&avgTimeRecord[i], header[0] );
}


/*
 * Send the time records labels
 */
void TM_timeLabelsTelemetry(){
    // Get array of all TimeRecord pointers and how many
    TimeRecord **allTR = MAIN_getAllTimeRecord();
    int nAllTR = MAIN_getNAllTimeRecord();
    
    // Initialize variables to extract the TimeRecord labels
    char labels[nAllTR][LABEL_LENGTH];
    String labels_str[nAllTR];

    // Iterate through all TimeRecord objects
    for( int i=0 ; i<nAllTR ; i++ ){
        // Get label
        labels_str[i] = allTR[i]->getLabel();

        // Copy the character array into a String. This will force all
        // labels to have the same length
        for( int j=0 ; j<LABEL_LENGTH ; j++ ){
            if( j < labels_str[i].length() ) labels[i][j] = labels_str[i][j];
            else labels[i][j] = 0;
        }
    }

    // Prepare header to send
    uint8_t header[3] = {sizeof(labels[0]), sizeof(labels)/sizeof(labels[0]), TEL_TIMELABELS};
    COMM_write( header, 3 );

    // Send all labels
    for( int i=0 ; i<nAllTR ; i++ )
        COMM_write( (uint8_t*)labels[i], header[0] );
}


/*
 * Notifies the end of Telemetry transmission
 */
void TM_end(){
    COMM_write( ENDOFTM );
    COMM_flush();
    pendingTM = false;
}


/*
 * Start sending telemetry
 */
void TM_start(){  
    if( pendingTM ){
        // Record Telemetry time
        tTelemetry.trigger();

        // Send TM identifier
        COMM_write( TELEMETRY );

        // Send time telemetry
        TM_timeTelemetry();

        // Check pending motor speed telemetry
        if( pendingMotorSpeedTM ){
            TM_mSpeedTelemetry();
            pendingMotorSpeedTM = false;
        }

        // Check pending time labels TM
        if( pendingTimeLabelsTM ){
            TM_timeLabelsTelemetry();
            pendingTimeLabelsTM = false;
        }
        
        TM_end();      
    }
}


/*
 * Check if a telemetry petition needs to be sent
 */  
void TM_checkTelemetry(){
    // Send TM petition each TELEMETRYTIME period
    if( (!pendingTM) && ((millis() - timer) >= TELEMETRYTIME) ){
        timer = millis();
        COMM_write( TM_PETITION );
        COMM_flush();
        pendingTM = true;
    }    
}


/*
 * Cancel pending telemetry
 */
void TM_cancel(){
    pendingTM = false;
}


/*
 * Pending telemetry functions
 */
void TM_pendMotorSpeed(){ pendingMotorSpeedTM = true; }
void TM_pendTimeLabels(){ pendingMotorSpeedTM = true; }
