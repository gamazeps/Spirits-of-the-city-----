#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "thread.h"

bool presence_detected = FALSE;
static WORKING_AREA(waPIRThread, 128);

__attribute__((__noreturn__))  static msg_t PIRThread(void *arg) {
  (void)arg;
  chRegSetThreadName("PIR");
  while(TRUE) {
    if (palReadPad(GPIOC, GPIOC_PROXSENSOR)==PAL_HIGH)
      presence_detected = TRUE;
    else
      presence_detected = FALSE:

    chThdSleepMilliseconds(PRESENCE_CHECK_TIME_MILLISECONDS);
  }
}

void startPirThread(void){
  chThdCreateStatic(waPIRThread, sizeof(waPIRThread), NORMALPRIO, PIRThread, NULL);
}

