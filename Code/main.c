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
#include "chprintf.h"
#include "debug.h"
#include "hsv2rgb.h"
#include "led.h"
#include "thread.h"
#include <stdint.h>


// Debug channel
BaseSequentialStream *chp =  (BaseSequentialStream *)&SD1;

// Timer 2 ans 3 PWM configuration structure (same config for both PWM drivers)
static PWMConfig pwmcfg = {
  800000,                             // 800kHz tick clock frequency
  256,                                // 256 ticks per PWM period
  NULL,
  {
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL}
  },
  /* HW dependent part.*/
  0,
  0
};

/*
 * Application entry point.
 */
int main(void) {
  // Initialize system
  halInit();
  chSysInit();

  // Activate USART1 using default configuration (115200 8N1)
  sdStart(&SD1, NULL);

  // Activate ADC
  adcStart(&ADCD1,NULL);

  // Initializes the PWM driver 3 and 4. Output are routed to LEDs in board.h
  pwmStart(&PWMD2, &pwmcfg);
  pwmStart(&PWMD3, &pwmcfg);

  // Launch the LED thread
  startLedThread();

  // Launch the heart beat thread
  startHeartBeatThread();

  //Launch ADC Thread
  startAdcThread();
  // Launch PIR thread
  startPirThread();

  // Output some things on the serial port but mainly sleep
  while (TRUE) {
    chThdSleepSeconds(1);
  }

}

//Return pseudo-random number between 1~3
uint8_t nextSequence(void){
  static uint16_t lfsr = 0xACE1u;
  uint8_t bit;
  uint8_t result;

  /* taps: 16 5 4 3; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
  bit  = ((lfsr >> 0) ^ (lfsr >> 11) ^ (lfsr >> 12) ^ (lfsr >> 13) ) & 1;
  lfsr =  (lfsr >> 1) | (bit << 15);
  result = (uint8_t) lfsr & 0xFF;
  if(result < 85)
    result = 1;
  else if(result < 170)
    result = 2;
  else
    result = 3;
  return result;
}





