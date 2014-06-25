#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "hsv2rgb.h"
#include "led.h"
#include "thread.h"

volatile bool run_led_thread = FALSE;
static WORKING_AREA(waLEDThread, 128);
__attribute__((__noreturn__))  static msg_t LEDThread(void *arg) {
  (void)arg;
  chRegSetThreadName("LED");
  static uint8_t h = 0;
  static uint8_t s = 255;
  static uint8_t v = 0;
  static int delta_v = 1;
  while (TRUE) {
    if(run_led_thread) {
      h += 1;
      v = v+delta_v;
      if (v==80)
        delta_v = -1;
      else if (v==0)
        delta_v = 1;

      set_big_led_hsv(h, s, v);
      set_small_led_hsv((h+128)%256, s, 80-v);
    }
    else {
      set_big_led_hsv(0, 0, 0);
      set_small_led_hsv(0, 0, 0);
    }

    chThdSleepMilliseconds(10);
  }
}

void startLedThread(void){
    chThdCreateStatic(waLEDThread, sizeof(waLEDThread), NORMALPRIO, LEDThread, NULL);
}
