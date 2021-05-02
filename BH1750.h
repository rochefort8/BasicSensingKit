#ifndef BH1750_H
#define BH1750_H

#include "Arduino.h"
#include <Wire.h>
#include <math.h>

class BH1750 {
public:
  BH1750(void) {}
  void begin();
  int read(uint16_t *p_value);

private:  
  bool on_off ;
  bool started ;
} ;

#endif