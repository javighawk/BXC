#ifndef TimeRecord_HPP
#define TimeRecord_HPP


/*****************************************/
/**************** INCLUDES ***************/
/*****************************************/

#include "Arduino.h"

/*****************************************/
/**************** DEFINES ****************/
/*****************************************/

#define AVG_RECORDS       100
#define LABEL_LENGTH        6

/*****************************************/
/**************** VARIABLES **************/
/*****************************************/


/*******************************************/
/**************** FUNCTIONS ****************/
/*******************************************/

class TimeRecord{
  public:
      TimeRecord(String label);
      void TIME_trigger();
      void TIME_stop();
      void TIME_resetMaxTRec(){_tRec_max = 0;};
      unsigned long TIME_getTime(){ return _tRec; }
      unsigned long TIME_getMaxTime(){ return _tRec_max; }
      unsigned long TIME_getAvgTime(){ return (unsigned long)(_tRec_avg/_iter); }
      String TIME_getLabel(){ return _label; }
  private:
      unsigned long _tRec;
      unsigned long _tRec_back;
      unsigned long _tRec_max;
      unsigned long _tRec_avg;
      String _label;
      unsigned int _iter;
};

#endif
