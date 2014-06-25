#include "RF.h"

static WORKING_AREA(waRFThread, 128);
__attribute__((__noreturn__)) static msg_t RFThread(void *arg){
  (void) arg;
  (void) rxbuf;
  chRegSetThreadName("RF");
  extStart(&EXTD1, &extconfig);

   // Test SPI
  static SPIConfig spi2cfg = {
    NULL, // No callback
    /* HW dependent part.*/
    GPIOB_RF_NSS, // CS is PB12
    12,// CS is PB12
    0x00000038, // CR1 : clock as low as possible 5:3=111
    0x00000000//CR2 what to put ?
  };
  // Init SPI
  spiStart(&SPID2, &spi2cfg);//get the SPI out of the "low power state"
  ConfigureRF(SIZEPKT);//Configure the RF device
  switchOff();
  ExecuteCommand(FLUSH_RX);//Clean the RX FIFO
  WriteRegisterByte(STATUS, RX_DR);
  chThdSleepMilliseconds(1);
  //Send some things
  txbuf[0]=0xAB;
  txbuf[1]=0x57;
  txbuf[2]=0x26;
  SendMessage(txbuf);
  ReceiveMessage();
}

void startRFthread(void){
chThdCreateStatic(waRFThread, sizeof(waRFThread), NORMALPRIO, RFThread, NULL);
}
