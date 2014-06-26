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
  uint8_t color;
  chRegSetThreadName("LED");
  while(TRUE){
    // XXX TODO : change this to use a semaphore !!!
    if(presence_detected){
      switch(lfsr()%ANIMS_NUMBER){
      case 0:
        animation_0();
        break;
      case 1:
        color = lfsr()%256;
        animation_1(50, color, (color+123)%256);
        break;
      case 2:
        color = lfsr()%256;
        animation_2(0, color, (color+123)%256);
        break;
      case 3:
        color = lfsr()%256;
        animation_3(color);
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
