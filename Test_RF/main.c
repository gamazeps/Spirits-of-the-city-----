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

static pwmcallback_t clear_all(void){
  palClearPad(GPIOF,GPIOF_STAT1);
  palClearPad(GPIOF,GPIOF_STAT2);
  palClearPad(GPIOF,GPIOF_STAT3);
  return 0;
}

static void set_green(PWMDriver *pwmd){
  (void)pwmd;
  palSetPad(GPIOF, GPIOF_STAT1);
}

static void set_orange(PWMDriver *pwmd){
  (void)pwmd;
  palSetPad(GPIOF, GPIOF_STAT2);
}

static void set_red(PWMDriver *pwmd){
  (void)pwmd;
  palSetPad(GPIOF, GPIOF_STAT3);
}
/*
 * Green LED blinker thread, times are in milliseconds.
 */
static PWMConfig pwmcfg =
  {
    200000,/*20 kHz clock frequency */
    64, /*PWM period 0.005 second*/
    (pwmcallback_t) clear_all, /*No callback*/
    {
      {PWM_OUTPUT_DISABLED,set_green},
      {PWM_OUTPUT_DISABLED,set_orange},
      {PWM_OUTPUT_DISABLED,set_red},
      {PWM_OUTPUT_DISABLED,NULL}
    },
    0,0
  };

static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *arg) {
  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE) {
    for(int i = 0;i<63;i++){
      pwmEnableChannel(&PWMD5,0,64-i);
      pwmEnableChannel(&PWMD5,1,64-i);
      pwmEnableChannel(&PWMD5,2,64-i);
      chThdSleepMilliseconds(50);
    }
  }
  return 0;
}

static SPIConfig spi3cfg = {
  NULL, // No callback
  /* HW dependent part.*/
  GPIOC, // CS is PC6
  6, // CS is PC6
  0x00000038 // CR1 : clock as low as possible 5:3=111
};

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  pwmStart(&PWMD5, &pwmcfg);
  spiStart(&SPID3, &spi3cfg);
  /*
   * Activates the serial driver 6 using the driver default configuration.
   */
  sdStart(&SD6, NULL);

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  // test SPI



  // Go to bed
  while (TRUE) {
    chThdSleepMilliseconds(1000);
  }
}
