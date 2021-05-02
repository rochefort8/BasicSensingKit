
#include "Arduino.h"

#include "Blink.h"
#include "Sensors.h"
#include "BT_HC05.h"
#include "DS323x_Rtc.h"

Blink blink ;
Sensors sensors ;
BT_HC05 bt ;
DS323x_Rtc rtc ;

void setup() {
  Serial.begin(115200);
  blink.begin() ;
  sensors.begin() ;
  bt.begin() ;
  rtc.begin() ;
}

void loop() {
  blink.blink() ;
  sensors.read() ;

  DateTime now = rtc.get();
  Serial.println(now.timestamp());

//  bt.read() ;
//  bt.write() ;

  delay(1000);                       // wait for a second
}