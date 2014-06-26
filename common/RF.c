#include "ch.h"
#include "hal.h"
#include "RF.h"
#include "radio_thread.h"
#include "debug.h"

uint8_t rxbuf = {0};

void set_CE(int on){
  on ? palSetPad(GPIOB, GPIOB_RF_CE) : palClearPad(GPIOB, GPIOB_RF_CE);
}

void spiStartTransaction(void) {
  chThdSleepMilliseconds(1);
  spiSelect(&SPID2);
  chThdSleepMilliseconds(1);
}

void spiStopTransaction(void) {
  chThdSleepMilliseconds(1);
  spiUnselect(&SPID2);
  chThdSleepMilliseconds(1);
}

void WriteRegister(int  numRegistre, int numMots, uint8_t* wtxbuf){
  spiStartTransaction();
  uint8_t command = W_REGISTER(numRegistre);
  spiSend(&SPID2, 1, &command);
  spiSend(&SPID2, numMots, wtxbuf);
  spiStopTransaction();
}

void WriteRegisterByte(int numRegister, uint8_t value) {
  WriteRegister(numRegister, 1, &value);
}

void ReadRegister(int numRegister, int numBytes, uint8_t* rrxbuf ){
  uint8_t command = R_REGISTER(numRegister);
  spiStartTransaction();
  spiSend(&SPID2, 1, &command);
  spiReceive(&SPID2, numBytes, rrxbuf);
  spiStopTransaction();
}

uint8_t ReadRegisterByte(int numRegister) {
  uint8_t value;
  ReadRegister(numRegister, 1, &value);
  return value;
}

void ExecuteCommand(int command) {
  spiStartTransaction();
  spiSend(&SPID2, 1, &command);
  spiStopTransaction();
}

//To send data to an other radio, puts the data int the TX_PAYLOAD
void SendData(const uint8_t* datasend, int numWords){
  set_CE(0);
  spiStartTransaction();
  uint8_t command = W_TX_PAYLOAD;
  spiSend(&SPID2, 1, &command);
  spiSend(&SPID2, numWords, datasend);
  spiStopTransaction();
  set_CE(1);
  chThdSleepMilliseconds(1);
  set_CE(0);
}

void ReceivePacket(uint8_t *rrxbuf, size_t pkt_size) {
  set_CE(1);//sets CE to 1
  msg_t msgMode = chSemWaitTimeout(&sem, 1000);
  if(msgMode == RDY_OK){chprintf(chp, "je reçois \r\n");
    set_CE(0);
    uint8_t command = R_RX_PAYLOAD;
    spiStartTransaction();chprintf(chp, "command=%x\r\n", command);
    spiSend(&SPID2, 1, &command);
    spiReceive(&SPID2, pkt_size, rrxbuf);chprintf(chp, "la commande est passée \r\n");chprintf(chp, "rrxbuf[31]=%x\r\n", rrxbuf[31]);
    spiStopTransaction();
    WriteRegisterByte(STATUS, RX_DR);
  }
  else if(msgMode == RDY_TIMEOUT) {
    set_CE(0);chprintf(chp, "time is up \r\n");
  }
}

void ConfigureRF(int sizepck){
  //Configure the register 00 (config)
  WriteRegisterByte(CONFIG, ISTRANSMITTER ? 0b000001110 : 0b00001111);
  //Disable the auto-ACK
  WriteRegisterByte(EN_AA, 0);
  //chosing channels
  WriteRegisterByte(EN_RXADDR, 1);
  //Adress width (1 => 3 bytes)
  WriteRegisterByte(SETUP_AW, 1);
  //set retransmission to 0
  WriteRegisterByte(SETUP_RTR, 0);
  //set the number of channels used
  WriteRegisterByte(RF_CH, 2);
  //??
  WriteRegisterByte(RF_SETUP, 0x07);
  //setting the  adress and the payload width
  uint8_t addr[3];
  addr[0]=0xB1;addr[1]=0xB2;addr[2]=0xB3;
  if(ISTRANSMITTER) {
    WriteRegister(TX_ADDR,3,addr);
  } else {
    WriteRegister(RX_ADDR_P0, 3, addr);
    WriteRegisterByte(RX_PW_P0, sizepck);
  }
}

void switchOn(void){
  WriteRegisterByte(CONFIG, ISTRANSMITTER ? 0b000001110 : 0b00001111);
}

void switchOff(void){
  WriteRegisterByte(CONFIG, ISTRANSMITTER ? 0b000001100 : 0b00001101);
}

void SendMessage(uint8_t* stxbuf) {
  if(ISTRANSMITTER){
    // int t=chTimeNow();
    while( TRUE /*(int) chTimeNow() < (int) (t+7000) */  ){
      SendData(stxbuf,SIZEPKT);
    }
  }
}

void ReceiveMessage(void){
  if(!ISTRANSMITTER){
    while (TRUE) {
      chThdSleepMilliseconds(5);
      // switchOn();
      uint8_t messagerecu[32];
      // Wait for data to be present in the RX FIFO
      ReceivePacket(messagerecu,SIZEPKT);
      chprintf(chp, "rxbuf[0]=%x\r\n",messagerecu[0]);
      chprintf(chp, "rxbuf[1]=%x\r\n",messagerecu[1]);
      rxbuf[0]=messagerecu[0];
      chThdSleepMilliseconds(1);
      // switchOff();
    }
  }
}

void irq_handler(EXTDriver *e, expchannel_t c){
  (void) e;
  (void) c;
  chSysLockFromIsr();
  chSemSignalI(&sem);
  chSysUnlockFromIsr();
}
