#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "led_thread.h"
#include "pir_thread.h"
#include "animation.h"
#include "lfsr.h"
#include "../common/sem.h"
#include <stdint.h>

static WORKING_AREA(waLEDThread, 128);
__attribute__((__noreturn__))  static msg_t LEDThread(void *arg) {
  (void)arg;
  uint8_t color;
  chRegSetThreadName("LED");
  while(TRUE){
    chSemWait(presence_sem);
      switch(lfsr()%3){
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
      case 4:
        color = lfsr()%256;
        animation_4(color);
        break;
      case 5: animation_5(); break;
      case 6: animation_6(); break;
      case 7: animation_7(); break;
      default :
        break;
      }
      chThdSleepSeconds(1);
    }
      chSemSignal(animation_sem);
    chThdSleepSeconds(1);

  }
}

void startLedThread(void){
  chThdCreateStatic(waLEDThread, sizeof(waLEDThread), NORMALPRIO, LEDThread, NULL);
}
