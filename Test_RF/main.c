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

#define ISTRANSMITER FALSE
//RF registers and function names
#define R_REGISTER(x) (x & 0x1F)
#define W_REGISTER(x) ((x & 0x1F) | 0x20)
#define NOP (0xff)
#define R_RX_PAYLOAD (0x61)
#define W_TX_PAYLOAD (0xA0)
#define FLUSH_RX (0xE2)
#define FLUSH_TX (0xE1)

#define CONFIG (0x00)
#define EN_AA (0x01) 
#define EN_RXADDR (0x02)
#define SETUP_AW (0x03) 
#define SETUP_RTR (0x04)
#define RF_CH (0x05)
#define RF_SETUP (0x06)
#define STATUS (0x07)
//It doesn't seem relevant to use registers 08 and 09 in our situation,neither 0B to 0F
#define RX_ADDR_P0 (0x0A)
#define TX_ADDR (0x10)
#define RX_PW_P0 (0x11)


static void set_green(int on){
  on ? palSetPad(GPIOF, GPIOF_STAT1) : palClearPad(GPIOF, GPIOF_STAT1);
}

static void set_orange(int on){
  on ? palSetPad(GPIOF, GPIOF_STAT2) : palClearPad(GPIOF, GPIOF_STAT2);
}

static void set_red(int on){
  on ? palSetPad(GPIOF, GPIOF_STAT3): palClearPad(GPIOF, GPIOF_STAT3);
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
 static uint8_t txbuf[512];
  static uint8_t rxbuf[512]; 
// en argument, le nom du registre ou il faut écrire et le nombre de mots à écrire
void WriteRegister(int  numRegistre, int numMots, uint8_t* wtxbuf, uint8_t* wrxbuf){
  wtxbuf[0] = W_REGISTER(numRegistre);
  spiSelect(&SPID3);
  spiExchange(&SPID3, numMots+1, wtxbuf, wrxbuf);
  spiUnselect(&SPID3);
  chThdSleepMilliseconds(1);
}
//registre dans lequel on va lire, et nombre de mots à lire
void ReadRegister(int numRegistre,int numMots,uint8_t* rtxbuf, uint8_t* rrxbuf ){
  rtxbuf[0] = R_REGISTER(numRegistre);
  for(int i=1; i<numMots+1;i++){
    rtxbuf[i]=NOP;
  }
  spiSelect(&SPID3);
  spiExchange(&SPID3, numMots+1, rtxbuf, rrxbuf);
  spiUnselect(&SPID3);
  chThdSleepMilliseconds(1);
}
//To send data to an other radio, puts the data int the TX_PAYLOAD
void SendData(uint8_t* datasend,int numWords,uint8_t* srxbuf){
datasend[0]=W_TX_PAYLOAD;
spiSelect(&SPID3);
spiExchange(&SPID3, numWords+1, datasend, srxbuf);
spiUnselect(&SPID3);
chThdSleepMilliseconds(1);
set_red(1);chThdSleepMilliseconds(100);
set_red(0);
}

void ReceiveData(uint8_t* rtxbuf,uint8_t* rrxbuf,int sizepck){
set_red(0);
rtxbuf[0]=R_RX_PAYLOAD;
for(int i=1; i<sizepck+1;i++){
    rtxbuf[i]=NOP;
  }
spiSelect(&SPID3);
spiExchange(&SPID3,sizepck+1, rtxbuf, rrxbuf);
spiUnselect(&SPID3);
chThdSleepMilliseconds(1);
set_red(1);
}

void ConfigureRF(int sizepck){
  //Configure the register 00 (config)
  if(ISTRANSMITER==TRUE){
    txbuf[1]=0b00000010;
  }
  else {
    txbuf[1]=0b00000011;
  }
  WriteRegister(CONFIG,1,txbuf, rxbuf);chThdSleepMilliseconds(1);
  //Disable the auto-ACK
  txbuf[1]=0b00000000;
  WriteRegister(EN_AA,1,txbuf,rxbuf);chThdSleepMilliseconds(1);
  //chosing channels
  txbuf[1]=0b00000001;
  WriteRegister(EN_RXADDR,1,txbuf,rxbuf);chThdSleepMilliseconds(1);
  //Adress width
  txbuf[1]=0b00000001;
  WriteRegister(SETUP_AW,1,txbuf,rxbuf);chThdSleepMilliseconds(1);
  //set retransmission to 0
  txbuf[1]=0b00000000;
  WriteRegister(SETUP_RTR,1,txbuf,rxbuf);chThdSleepMilliseconds(1);
  //set the number of channels used
  txbuf[1]=0b00000010;
  WriteRegister(RF_CH,1,txbuf,rxbuf);chThdSleepMilliseconds(1);
  //??
  txbuf[1]=0b00000101;
  WriteRegister(RF_SETUP,1,txbuf,rxbuf);chThdSleepMilliseconds(1);
  //setting the  adress and the payload width
  txbuf[1]=0xB1;txbuf[2]=0xB2;txbuf[3]=0xB3;
  if(ISTRANSMITER==TRUE){
    WriteRegister(TX_ADDR,3,txbuf,rxbuf);chThdSleepMilliseconds(1);
  }
  else{
    WriteRegister(RX_ADDR_P0,3,txbuf,rxbuf);chThdSleepMilliseconds(1);
    txbuf[1]=sizepck;
    WriteRegister(RX_PW_P0,1,txbuf,rxbuf);chThdSleepMilliseconds(1);
  }
}

//  Application entry point.
int main(void) {
  halInit();//also initializes the spi driver
  chSysInit();

  // Creates the blinker thread.
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, BlinkerThread, NULL);

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
  // Send some things
  while (TRUE) {
    // Read PIPE0 addr register
    ConfigureRF(1);
    // Read PIPE0 addr register

    chThdSleepMilliseconds(1000);
  }
}
