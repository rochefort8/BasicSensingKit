#ifndef BT_HC05_H
#define BT_HC05_H

#include "Arduino.h"
#include <SoftwareSerial.h>

#define btport Serial1

class BT_HC05 {
public:
  void begin() {
    btport.begin(9600);      
  }
  int read(void) {
    if (btport.available()) {
        Serial.write(btport.read());
    }
  }
  int write(void) {
    if (Serial.available()){
       btport.write(Serial.read());              
    }
  }
private:  
} ;

#endif
