#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "led_thread.h"
#include "animation.h"
#include "lfsr.h"
#include "radio_thread.h"
#include "../common/sem.h"
#include <stdint.h>

static WORKING_AREA(waLEDThread, 128);
__attribute__((__noreturn__))  static msg_t LEDThread(void *arg) {
  (void)arg;
  uint8_t color;
  chRegSetThreadName("LED");
  while(TRUE){
    chSemWait(&presence_sem);
    txbuf[0]=lfsr()%8; //choose of an animation (alea)
    switch(txbuf[0]){ 
      //txbuf -> parameters for the slaves
      //rxbuf -> parameters for the master
      case 0:
        break;

      case 1:
        color = lfsr()%256;
	txbuf[1]=50;
	txbuf[2]=color;
	txbuf[3]=(color+123)%256;

        color = lfsr()%256;
	rxbuf[1]=50;
	rxbuf[2]=color;
	rxbuf[3]=(color+123)%256;
        break;

      case 2:
        color = lfsr()%256;
	txbuf[1]=100;
	txbuf[2]=color;
	txbuf[3]=(color+123)%256;

        color = lfsr()%256;
	rxbuf[1]=0;
	rxbuf[2]=color;
	rxbuf[3]=(color+123)%256;
        break;

      case 3:
        txbuf[1]=lfsr()%256;
        rxbuf[1]=lfsr()%256;
        break;

      case 4:
        txbuf[1]=lfsr()%256; 
        rxbuf[1]=lfsr()%256;
        break;

      case 5: break;

      case 6: break;

      case 7:  break;

      default : break;
      }

      chSemSignal(&animation_sem);
      chThdSleepSeconds(1);
  }
}

void startLedThread(void){
  chThdCreateStatic(waLEDThread, sizeof(waLEDThread), NORMALPRIO, LEDThread, NULL);
}
