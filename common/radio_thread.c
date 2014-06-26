#include "ch.h"
#include "hal.h"
#include "RF.h"
#include "radio_thread.h"
#include "debug.h"

static WORKING_AREA(waRFThread, 512);
__attribute__((__noreturn__)) static msg_t RFThread(void *arg){
  (void) arg;
  chRegSetThreadName("RF");
  extStart(&EXTD1, &extconfig);

  // Init SPI
  static SPIConfig spi2cfg = {
    NULL, // No callback
    /* HW dependent part.*/
    GPIOB, // CS is PB12
    12,// CS is PB12
    0x00000038, // CR1 : clock as low as possible 5:3=111
  };

  // Get the SPI out of the "low power state"
  spiStart(&SPID2, &spi2cfg);

  // Configure the RF device
  ConfigureRF(SIZEPKT);
  //switchOff();
  // Clean the RX FIFO
  //ExecuteCommand(FLUSH_RX);
  WriteRegisterByte(STATUS, RX_DR);
  chThdSleepMilliseconds(1);
  while(TRUE){
    ReceiveMessage();}
  /* uint8_t mess[32];
  //txbuf[0]=0xAB;
  //txbuf[1]=0x57;
  //txbuf[2]=0x26;
  mess[0]=0xAB;
  mess[1]=0x94;
  mess[2]=0xe4;
  while(TRUE) {
    //Send some things
    // SendMessage(messtxbuf);*/

}

void startRFThread(void){
chThdCreateStatic(waRFThread, sizeof(waRFThread), NORMALPRIO, RFThread, NULL);
}
