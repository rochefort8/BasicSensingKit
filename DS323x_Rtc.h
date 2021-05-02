#ifndef RTC_H
#define RTC_H

#include "Arduino.h"
#include <DS323x.h>
#include <Wire.h>

class DS323x_Rtc {
public:
  void begin() { 
    Wire.begin() ;
    delay(2000) ;
    rtc.attach(Wire);
  };
  DateTime get(void) {
    return rtc.now() ;
  }

private:  
  DS323x rtc;
} ;

#endif