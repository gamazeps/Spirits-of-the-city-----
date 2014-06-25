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
static WORKING_AREA(waLEDThread, 128);
__attribute__((__noreturn__))  static msg_t LEDThread(void *arg) {
  (void)arg;
  chRegSetThreadName("LED");
  int8_t x=2;
  switch(x){
  case 0:
    chprintf(chp,"Je vais lancer la premiere animation");
    animation_1();
    chprintf(chp,"J'ai fini la premiere animation");
    break;
  case 1:
    chprintf(chp,"Je vais lancer la deuxième animation");
    animation_2(4,50,120);
    chprintf(chp,"Je sais pas pourquoi je ne suis pas censé etre la");
    break;
  case 2:
    animation_3(0, 20, 180);
  default :
    chprintf(chp,"Bordel !");
    animation_1();
  }
  while(TRUE){
    chprintf(chp,"Dodo");
    chThdSleepSeconds(10);
  }
}
void startLedThread(void){
    chThdCreateStatic(waLEDThread, sizeof(waLEDThread), NORMALPRIO, LEDThread, NULL);
}
