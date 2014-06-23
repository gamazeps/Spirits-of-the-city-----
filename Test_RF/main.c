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

#define R_REGISTER(x) (x & 0x1F)
#define W_REGISTER(x) ((x & 0x1F) | 0x20)
#define NOP (0xff)

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

  txbuf[1] =0xe4;
  txbuf[2]=0x05;
  txbuf[3]=0x17;
  txbuf[4]=0xe7;

  // Send some things
  while (TRUE) {
    // Read PIPE0 addr register
    WriteRegister(0x0A,5,txbuf, rxbuf);
    ReadRegister(0x0A,5,txbuf, rxbuf);
    // Read PIPE0 addr register

    // Configuration in TX mode
    txbuf[1]=0b00000010;
    WriteRegister(0x00,1,txbuf,rxbuf);
    // Adress settings
    txbuf[1]=0b00000001;// address width
    WriteRegister(0x03,1,txbuf,rxbuf);
    txbuf[1]=0xB1;
    txbuf[2]=0xB2;
    txbuf[3]=0xB3;
    WriteRegister(0x10,3,txbuf,rxbuf); //Fixation of the Transmiter address
    WriteRegister(0x0A,3,txbuf,rxbuf); // Fixation of the RX_ADDR_P0
    //Checking the values of the registers
    ReadRegister(0x00,1,txbuf,rxbuf);
    ReadRegister(0x03,1,txbuf,rxbuf);
    ReadRegister(0x10,3,txbuf,rxbuf);
    ReadRegister(0x0A,3,txbuf,rxbuf);

    chThdSleepMilliseconds(1000);
  }
}
