#include "ch.h"
#include "hal.h"
#include "debug.h"
#include "pir_thread.h"
#include "../common/sem.h"

// Définit tous les combien on regarde s'il y a un passant
#define PRESENCE_CHECK_TIME_MILLISECONDS 100

volatile bool presence_detected = FALSE;
static WORKING_AREA(waPIRThread, 128);
__attribute__((__noreturn__)) static msg_t PIRThread(void *arg) {
  (void)arg;
  chRegSetThreadName("PIR");
  while(TRUE) {
    if(palReadPad(GPIOC, GPIOC_PROXSENSOR)==PAL_HIGH){
      chBSemSignal(presence_sem);
    }
    else
      presence_detected = FALSE;
  }
}

void startPirThread(void){
  chThdCreateStatic(waPIRThread, sizeof(waPIRThread), NORMALPRIO, PIRThread, NULL);
}
