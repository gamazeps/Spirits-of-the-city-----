#include "ch.h"
#include "hal.h"
#include "animation.h"
#include "lfsr.h"
#include "radio_thread.h"
#include <stdint.h>

void fill_buffer(void) {
  uint8_t color;
  txbuf[0]=lfsr()%8;
  rxbuf[0]=txbuf[0]; //choose of an animation (alea)
  switch(txbuf[0]){
    //txbuf -> parameters for the slaves
    //rxbuf -> parameters for the master
  case 0:
    break;
  case 1:
    color = lfsr()%256;
    txbuf[1]=30;
    txbuf[2]=color;
    txbuf[3]=(color+123)%256;

    color = lfsr()%256;
    rxbuf[1]=30;
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


}
