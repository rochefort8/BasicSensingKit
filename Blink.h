
#ifndef BLINK_H
#define BLINK_H

#include "Arduino.h"

class Blink {
public:
  Blink(void) { on_off = false ; started = false ; }

  void begin() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    started = true ;
  }
  void timer (int count) { this->blink(); }
  void blink(void) {
    if ( !started ) return ;
    digitalWrite(LED_BUILTIN, (on_off == true)? HIGH : LOW );  
    on_off = !on_off ;
  }
private:  
  bool on_off ;
  bool started ;
} ;

#endif