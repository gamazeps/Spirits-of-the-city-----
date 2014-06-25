/*
  ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include "ch.h"
#include "hal.h"

#define ISTRANSMITTER FALSE
//RF registers and function names
#define R_REGISTER(x) (x & 0x1F)
#define W_REGISTER(x) ((x & 0x1F) | 0x20)
#define NOP 0xff
#define R_RX_PAYLOAD 0x61
#define W_TX_PAYLOAD 0xA0
#define FLUSH_RX 0xE2
#define FLUSH_TX 0xE1

#define CONFIG 0x00
#define EN_AA 0x01
#define EN_RXADDR 0x02
#define SETUP_AW 0x03
#define SETUP_RTR 0x04
#define RF_CH 0x05
#define RF_SETUP 0x06
#define STATUS 0x07
//It doesn't seem relevant to use registers 08 and 09 in our situation,neither 0B to 0F
#define RX_ADDR_P0 0x0A
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define FIFO_STATUS 0x17
#define RX_EMPTY (1 << 0)
#define DYNP 0x1C
#define RX_DR (1 << 6)

static void set_green(int on){
  on ? palSetPad(GPIOF, GPIOF_STAT1) : palClearPad(GPIOF, GPIOF_STAT1);
}

static void set_orange(int on){
  on ? palSetPad(GPIOF, GPIOF_STAT2) : palClearPad(GPIOF, GPIOF_STAT2);
}

static void set_red(int on){
  on ? palSetPad(GPIOF, GPIOF_STAT3): palClearPad(GPIOF, GPIOF_STAT3);
}

static void spiStartTransaction(void) {
  chThdSleepMilliseconds(1);
  spiSelect(&SPID3);
  chThdSleepMilliseconds(1);
}

static void spiStopTransaction(void) {
  chThdSleepMilliseconds(1);
  spiUnselect(&SPID3);
  chThdSleepMilliseconds(1);
}

static uint8_t txbuf[128];
static uint8_t rxbuf[128];
static SEMAPHORE_DECL(sem, 0);
static msg_t msgMode;

// en argument, le nom du registre ou il faut écrire et le nombre de mots à écrire
static void WriteRegister(int  numRegistre, int numMots, uint8_t* wtxbuf){
  spiStartTransaction();
  uint8_t command = W_REGISTER(numRegistre);
  spiSend(&SPID3, 1, &command);
  spiSend(&SPID3, numMots, wtxbuf);
  spiStopTransaction();
}

static void WriteRegisterByte(int numRegister, uint8_t value) {
  WriteRegister(numRegister, 1, &value);
}

static void ExecuteCommand(int command) {
  spiStartTransaction();
  spiSend(&SPID3, 1, &command);
  spiStopTransaction();
}

//registre dans lequel on va lire, et nombre de mots à lire
void ReadRegister(int numRegister, int numBytes, uint8_t* rrxbuf ){
  uint8_t command = R_REGISTER(numRegister);
  spiStartTransaction();
  spiSend(&SPID3, 1, &command);
  spiReceive(&SPID3, numBytes, rrxbuf);
  spiStopTransaction();
}

static uint8_t ReadRegisterByte(int numRegister) {
  uint8_t value;
  ReadRegister(numRegister, 1, &value);
  return value;
}

//To send data to an other radio, puts the data int the TX_PAYLOAD
void SendData(const uint8_t* datasend, int numWords){
  set_red(0);
  spiStartTransaction();
  uint8_t command = W_TX_PAYLOAD;
  spiSend(&SPID3, 1, &command);
  spiSend(&SPID3, numWords, datasend);
  spiStopTransaction();
  set_red(1);
  chThdSleepMilliseconds(1);
  set_red(0);
}

volatile int status;

static void ReceivePacket(uint8_t *rxbuf, size_t pkt_size) {
 set_red(1);//sets CE to 1
 msgMode = chSemWaitTimeout(&sem,TIME_INFINITE);
 if(msgMode == RDY_OK){
   palTogglePad(GPIOF, GPIOF_STAT2);
   set_red(0);
   uint8_t command = R_RX_PAYLOAD;
   spiStartTransaction();
   spiSend(&SPID3, 1, &command);
   spiReceive(&SPID3, pkt_size, rxbuf);
   spiStopTransaction();
   WriteRegisterByte(STATUS, RX_DR);
 }
 else if(msgMode == RDY_TIMEOUT) {
   set_red(0);
   chSemSignal(&sem);set_orange(1);
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
  txbuf[0]=0xB1;txbuf[1]=0xB2;txbuf[2]=0xB3;
  if(ISTRANSMITTER) {
    WriteRegister(TX_ADDR,3,txbuf);
  } else {
    WriteRegister(RX_ADDR_P0, 3, txbuf);
    WriteRegisterByte(RX_PW_P0, sizepck);
  }
}

static void switchOn(void){
  WriteRegisterByte(CONFIG, ISTRANSMITTER ? 0b000001110 : 0b00001111);
}

static void switchOff(void){
  WriteRegisterByte(CONFIG, ISTRANSMITTER ? 0b000001100 : 0b00001101);
}

// Blinker thread
static WORKING_AREA(waThread1, 128);
static msg_t BlinkerThread(void *arg) {
  (void)arg;
  int on = 0;
    while (TRUE) {
    set_green(on);
    chThdSleepMilliseconds(500);
    on = 1-on;
  }
  return 0;
}

static WORKING_AREA(waThread2, 128);
static msg_t waThread2go(void *arg) {
  (void)arg;
   if (ISTRANSMITTER) {
    while (TRUE) {
      chThdSleepMilliseconds(1000);
      txbuf[0]=0x05;
      txbuf[1]=0x11;
      txbuf[2]=0x94;
      SendData(txbuf,3);
    }
    }else{
    while (TRUE) {
      chThdSleepMilliseconds(5000);
      // switchOn();
      // Wait for data to be present in the RX FIFO
      ReceivePacket(rxbuf, 3);
      chThdSleepMilliseconds(1);
      // switchOff();
      }
     }
  return 0;
}

static void irq_handler(EXTDriver *e, expchannel_t c){
	(void) e;
	(void) c;
	chSysLockFromIsr();
	chSemSignalI(&sem);
	chSysUnlockFromIsr();
}

static const EXTConfig extconfig={
  {
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_FALLING_EDGE | EXT_MODE_GPIOG | EXT_CH_MODE_AUTOSTART, irq_handler},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL}
  },
};


//  Application entry point.
int main(void) {
  halInit();//also initializes the spi driver
  chSysInit();
  extStart(&EXTD1, &extconfig);


  // Creates the blinker thread.
   // Test SPI
  static SPIConfig spi3cfg = {
    NULL, // No callback
    /* HW dependent part.*/
    GPIOC, // CS is PC6
    6,// CS is PC6
    0x00000038 // CR1 : clock as low as possible 5:3=111
  };
  // Init SPI
  spiStart(&SPID3, &spi3cfg);//get the SPI out of the "low power state"
  ConfigureRF(3);
  ExecuteCommand(FLUSH_RX);
  WriteRegisterByte(STATUS, RX_DR);
  rxbuf[0]=ReadRegisterByte(CONFIG);
  chThdSleepMilliseconds(1);
  //Send some things
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, BlinkerThread, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, waThread2go, NULL);
}
