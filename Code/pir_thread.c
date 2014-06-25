#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "thread.h"

// PIR sensor thread
static WORKING_AREA(waPIRThread, 128);

__attribute__((__noreturn__))  static msg_t PIRThread(void *arg) {
  (void)arg;
  chRegSetThreadName("PIR");  while(TRUE) {
    if (palReadPad(GPIOC, GPIOC_PROXSENSOR)==PAL_HIGH) {
      run_led_thread = TRUE;
      chThdSleepSeconds(10);
      run_led_thread = FALSE;
    }
    chThdSleepMilliseconds(100);
  }
}

void startPirThread(void){
  chThdCreateStatic(waPIRThread, sizeof(waPIRThread), NORMALPRIO, PIRThread, NULL);
}

