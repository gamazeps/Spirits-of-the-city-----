#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "led_thread.h"
#include "pir_thread.h"
#include "animation.h"
#include "lfsr.h"
#include <stdint.h>

static WORKING_AREA(waLEDThread, 128);
__attribute__((__noreturn__))  static msg_t LEDThread(void *arg) {
  (void)arg;
  chRegSetThreadName("LED");
  while(TRUE){
    // XXX TODO : change this to use a semaphore !!!
    if(presence_detected){
      switch(lfsr()%3){
      case 0:
        animation_1();
        break;
      case 1:
        animation_2(50, 50, 120);
        break;
      case 2:
        animation_3(0, 20, 180);
        break;
      default :
        break;
      }
      chThdSleepSeconds(1);
    }
    else
      chThdSleepMilliseconds(10);
  }
}

void startLedThread(void){
  chThdCreateStatic(waLEDThread, sizeof(waLEDThread), NORMALPRIO, LEDThread, NULL);
}
