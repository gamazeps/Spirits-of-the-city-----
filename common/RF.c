#include <string.h>
#include "ch.h"
#include "hal.h"
#include "RF.h"
#include "radio_thread.h"
#include "debug.h"

static SEMAPHORE_DECL(sem, 0);

uint8_t rxbuf[SIZEPKT] = {0};
uint8_t txbuf[SIZEPKT] = {0};

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

// Return TRUE if a packet has been received
int ReceivePacket(uint8_t *rrxbuf, size_t pkt_size, int timeout_ms) {
  set_CE(1);//sets CE to 1
  msg_t msgMode = chSemWaitTimeout(&sem, timeout_ms);
  if(msgMode == RDY_OK){
    set_CE(0);
    uint8_t command = R_RX_PAYLOAD;
    spiStartTransaction();
    spiSend(&SPID2, 1, &command);
    spiReceive(&SPID2, pkt_size, rrxbuf);
    spiStopTransaction();
    WriteRegisterByte(STATUS, RX_DR);
    return TRUE;
  }
  else if(msgMode == RDY_TIMEOUT) {
    set_CE(0);
  }
  return FALSE;
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
  switchOn();
  int t=chTimeNow();
  while((int) chTimeNow() < (int) (t+7000)){
    SendData(stxbuf,SIZEPKT);
  }
}

// Get the animation parameters in rxbuf and waits for the top if needed.
// Return TRUE if an animation is ready, 0 if not.
static int ReceiveAnimation(void) {
  switchOn();
  static uint8_t rxbuf2[SIZEPKT] = {0};
  int needs_start = 0;
  int received;
  while (TRUE) {
    received = ReceivePacket(rxbuf2, SIZEPKT, needs_start ? 10000 : 1000);
    if (!received)
      break;
    if (rxbuf2[0] == 0xff) {
      if (needs_start) {
        break;
      } else {
      // Top has no meaning here
      continue;
      }
    }
    memcpy(rxbuf, rxbuf2, SIZEPKT);
    if ((rxbuf2[0] & 0x80) == 0) {
      needs_start = 1;
    } else {
      break;
    }
  }
  switchOff();
  return received;
}

void WaitForAnimation(void) {
  while (TRUE) {
    int received = ReceiveAnimation();
    if (received) {
      break;
    }
    chThdSleepSeconds(5);
  }
}

void irq_handler(EXTDriver *e, expchannel_t c){
  (void) e;
  (void) c;
  chSysLockFromIsr();
  chSemSignalI(&sem);
  chSysUnlockFromIsr();
}
