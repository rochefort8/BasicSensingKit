#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"
#include <TimerTC3.h>

#define N_TABLES (10) 

typedef struct {
  void (* handler_p)(int);
} timer_table_t ;

class Timer ;
extern Timer *_this ;

class Timer {
  int timerCount ;
  timer_table_t table[N_TABLES] ;

  static void _timerIsr(void) {
    _this->timerIsr();    
  }

public:
  void begin();
  void timerIsr(void);
  void attachHandler(void (* handler_p)(int));
} ;


#endif
