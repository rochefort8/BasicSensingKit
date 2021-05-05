
#include "Arduino.h"

#include "Blink.h"
#include "Sensors.h"
#include "BT_HC05.h"
#include "DS323x_Rtc.h"
#include "Timer.h"

Blink blink ;
Sensors sensors ;
BT_HC05 bt ;
DS323x_Rtc rtc ;
Timer timer ;

void setup() 
{

  pinMode(A10, OUTPUT);
  digitalWrite(A10, LOW);  

  timer.begin();
  Serial.begin(115200);
  blink.begin() ;
  sensors.begin() ;
  bt.begin() ;
  rtc.begin() ;

}

void loop() {
  if (sensors.available()) {
    sensors.read() ;   
  }
}