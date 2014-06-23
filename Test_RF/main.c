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
  static uint8_t txbuf[512];
  static uint8_t rxbuf[512];
  for (int i=0; i<512; i++)
    txbuf[i] = i;

  // Send some things
  while (TRUE) {
    // Read PIPE0 addr register
    txbuf[0] = R_REGISTER(0xA);
    txbuf[1] = NOP;
    txbuf[2] = NOP;
    txbuf[3] = NOP;
    txbuf[4] = NOP;
    txbuf[5] = NOP;
    spiSelect(&SPID3);
    spiExchange(&SPID3, 6, txbuf, rxbuf);
    spiUnselect(&SPID3);
    chThdSleepMilliseconds(1);

    // Change PIPE0 addr register
    txbuf[0] = W_REGISTER(0xA);
    txbuf[1] = 0xaa;
    txbuf[2] = 0xE7;
    txbuf[3] = 0x23;
    txbuf[4] = 0xe7;
    txbuf[5] = 0x23;
    spiSelect(&SPID3);
    spiExchange(&SPID3, 6, txbuf, rxbuf);
    spiUnselect(&SPID3);
    chThdSleepMilliseconds(1);

    // Read PIPE0 addr register
    txbuf[0] = R_REGISTER(0xA);
    txbuf[1] = NOP;
    txbuf[2] = NOP;
    txbuf[3] = NOP;
    txbuf[4] = NOP;
    txbuf[5] = NOP;
    spiSelect(&SPID3);
    spiExchange(&SPID3, 6, txbuf, rxbuf);
    spiUnselect(&SPID3);
    chThdSleepMilliseconds(1);

    chThdSleepMilliseconds(1000);
  }
}
