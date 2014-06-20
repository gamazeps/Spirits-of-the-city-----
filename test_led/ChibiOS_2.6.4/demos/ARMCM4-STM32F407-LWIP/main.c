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
#include "test.h"

#include "lwipthread.h"

#include "web/web.h"

// static void clear_all (PWMDriver *pwmd)
// {
//   palSetPad(GPIOF, GPIOF_STAT1); 
//   palSetPad(GPIOF, GPIOF_STAT2);
//   palSetPad(GPIOF, GPIOF_STAT3);
// }

// static void set_green (PWMDriver *pwmd)
// {
//   palClearPad(GPIOF, GPIOF_STAT1);
// }

// static void set_orange (PWMDriver *pwmd)
// {
//   palClearPad(GPIOF, GPIOF_STAT2);

// }static void set_red (PWMDriver *pwmd)
// {
//   palClearPad(GPIOF, GPIOF_STAT3);
// }
  
// static PWMConfig pwmcfg = {
//   20000,
//   200,
//   clear_all,
//   {
//     {PWM_OUTPUT_DISABLED, set_green},
//     {PWM_OUTPUT_DISABLED, set_orange},
//     {PWM_OUTPUT_DISABLED, set_red},
//     {PWM_OUTPUT_DISABLED, NULL},
//   },
//   0,
//   0
// };

static ADCDriver adcp;
static const ADCConversionGroup grpp = {
  FALSE,
  10,
  NULL,
  NULL
};
static adcsample_t samples;

    

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker");

  msg_t adc_result;

  

  while (TRUE) {

    adcStart(&adcp,NULL);

    adc_result = adcConvert(&adcp, &grpp, &samples, 1);

    switch(adc_result){
      case RDY_OK :
        palSetPad(GPIOF, GPIOF_STAT1);
        chThdSleepMilliseconds(150);
        palClearPad(GPIOF, GPIOF_STAT1);
        chThdSleepMilliseconds(150);
        break;
      case RDY_RESET :
        palSetPad(GPIOF, GPIOF_STAT2);
        chThdSleepMilliseconds(150);
        palClearPad(GPIOF, GPIOF_STAT2);
        chThdSleepMilliseconds(150);
        break;
      case RDY_TIMEOUT :
        palSetPad(GPIOF, GPIOF_STAT3);
        chThdSleepMilliseconds(150);
        palClearPad(GPIOF, GPIOF_STAT3);
        chThdSleepMilliseconds(150);
        break;
    }

 //    for(int j=1; j<400; j++)
 //      {
	
	// int i = j < 200 ? j : 399 - j;
	// int k = (j+133)%400 < 200 ? (j+133)%400 : (399 - (j+133))%400;
	// int l = (j + 266)%400 < 200 ? (j+266)%400 : (399-(j+266))%400;

	// pwmEnableChannel(&PWMD4, 0, i);
	// pwmEnableChannel(&PWMD4, 1,k);
	// pwmEnableChannel(&PWMD4, 2, l);
	// chThdSleepMilliseconds(8);

  //    }
  }
  
}

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

  adcInit();
  adcObjectInit(&adcp);

  //pwmStart(&PWMD4, &pwmcfg);

  /*
   * Activates the serial driver 6 using the driver default configuration.
   */
  sdStart(&SD6, NULL);

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Creates the LWIP threads (it changes priority internally).
   */
  chThdCreateStatic(wa_lwip_thread, LWIP_THREAD_STACK_SIZE, NORMALPRIO + 1,
                    lwip_thread, NULL);

  /*
   * Creates the HTTP thread (it changes priority internally).
   */
  chThdCreateStatic(wa_http_server, sizeof(wa_http_server), NORMALPRIO + 1,
                    http_server, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (TRUE) {
    if (palReadPad(GPIOC, GPIOC_SWITCH_TAMPER) == 0)
      TestThread(&SD6);
    chThdSleepMilliseconds(500);
  }
}
