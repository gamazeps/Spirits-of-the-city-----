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

// Debug channel
BaseSequentialStream *chp =  (BaseSequentialStream *)&SD1;


// Timer 2 ans 3 PWM configuration structure (same config for both PWM drivers)
static PWMConfig pwmcfg = {
  100000,                             // 100kHz tick clock frequency
  100,                                // 100 ticks per PWM period thus PWM period is 1kHz
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

// Heartbeat thread
static WORKING_AREA(waHBT, 128);
__attribute__((__noreturn__))  static msg_t HBT(void *arg) {
  (void)arg;
  chRegSetThreadName("Heart Beat");
  static int i = 0;
  while (TRUE) {
    pwmEnableChannel(&PWMD3, 0, i);
    pwmEnableChannel(&PWMD3, 1, i);
    pwmEnableChannel(&PWMD3, 2, i);
    pwmEnableChannel(&PWMD3, 3, i);

    pwmEnableChannel(&PWMD2, 0, i);
    pwmEnableChannel(&PWMD2, 1, i);
    pwmEnableChannel(&PWMD2, 2, i);
    pwmEnableChannel(&PWMD2, 3, i);

    i = i+1;
    if (i>100)
      i = 0;
    chThdSleepMilliseconds(10);
  }
}

/*
 * Application entry point.
 */
int main(void) {
  // Initialize system
  halInit();
  chSysInit();

  // Activate USART1 using default configuration (115200 8N1)
  sdStart(&SD1, NULL);

  // Initializes the PWM driver 3 and 4. Output are routed to LEDs in board.h
  pwmStart(&PWMD2, &pwmcfg);
  pwmStart(&PWMD3, &pwmcfg);

  // Launch the heart beat thread
  chThdCreateStatic(waHBT, sizeof(waHBT), NORMALPRIO, HBT, NULL);

  // Output some things on the serial port but mainly sleep
  while (TRUE) {
    chprintf(chp, "Hello World!\r\n");
    chThdSleepSeconds(1);
  }
}
