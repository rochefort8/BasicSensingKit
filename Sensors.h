
#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"
#include "DHT.h"
#include "BH1750.h"
#include "DS323x_Rtc.h"
#include "BT_HC05.h"

typedef struct {
  float humidity, temperature ;
  uint16_t lx ;
} sensing_data_t ;

#define N_SENSING_DATA (10)
#define SENSING_INTERVAL_SECONDS (30)

class Sensors {
public:
  Sensors(void) { 
    m_available = false ;
    m_repeat = 0 ;
    m_sensing_interval = 0;
  }
  void begin() ;
  int read(void) ;
  int save(void) ;
  void timer(int count);
  bool available(void) { return m_available; }

private:  
  bool m_available ;
  int m_repeat ;
  int m_sensing_interval ;
  sensing_data_t data_table[N_SENSING_DATA] ;
  BH1750 bh1750 ;
} ;

#endif