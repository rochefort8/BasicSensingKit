#include "Timer.h"
#include "Blink.h"
#include "Sensors.h"
#include "BT_HC05.h"

extern Blink blink ;
extern Sensors sensors ;
extern BT_HC05 bt ;

Timer *_this = NULL ;

void Timer::begin() {
  _this = this ;
  timerCount = 0;
  for (int i = 0;i < N_TABLES;i++) {
    table[i].handler_p = NULL ;
  }
  TimerTc3.initialize(1000000);
  TimerTc3.attachInterrupt(_timerIsr);
}

void Timer::timerIsr(void) {
  for (int i = 0;i < N_TABLES;i++) {
    void (* handler_p)(int) = table[i].handler_p ;
    if (handler_p != NULL) {
      handler_p(timerCount) ;
    } 
  }

  blink.timer(timerCount) ;
  sensors.timer(timerCount);
  timerCount++ ;
} ;

void Timer::attachHandler(void (* handler_p)(int))
{
  for (int i = 0;i < N_TABLES;i++) {
    table[i].handler_p ;
    if (table[i].handler_p == NULL) {
      table[i].handler_p = handler_p ;
      break;
    } 
  }
}
