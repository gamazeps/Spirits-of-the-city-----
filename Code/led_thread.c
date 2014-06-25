#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "hsv2rgb.h"
#include "led.h"
#include "thread.h"
#include "animation1.h"
#include <stdint.h>

volatile bool run_led_thread = FALSE;

//Those definitions need to be put in Radio Thread
uint8_t RxBuf[32];
uint8_t TxBuf[32];

static WORKING_AREA(waLEDThread, 128);
__attribute__((__noreturn__))  static msg_t LEDThread(void *arg) {
  (void)arg;
  chRegSetThreadName("LED");
  while(TRUE){
    if(presence_detected){
      switch(nextSequence()){
      case 1:
        animation_1();
        break;
      case 2:
        animation_2(4,50,120);
        break;
      case 3:
        animation_3(0, 20, 180);
      default :
        animation_1();
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
