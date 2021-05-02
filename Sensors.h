
#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"
#include "DHT.h"
#include "BH1750.h"

class Sensors {
public:
  Sensors(void) { }
  void begin() ;
  int read(void) ;
  int save(void) ;
private:  
} ;

#endif