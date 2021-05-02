
#include "Arduino.h"

#include "Blink.h"
#include "Sensors.h"
#include "BT_HC05.h"

Blink blink ;
Sensors sensors ;
BT_HC05 bt ;

void setup() {
  Serial.begin(115200);
  blink.begin() ;
  sensors.begin() ;
  bt.begin() ;
}

void loop() {
  blink.blink() ;
  sensors.read() ;
  bt.read() ;
  bt.write() ;

  delay(1000);                       // wait for a second
}