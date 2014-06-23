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

static void clear_all (PWMDriver *pwmd){
  (void) pwmd;
  palClearPad(GPIOF, GPIOF_STAT1); 
  palClearPad(GPIOF, GPIOF_STAT2);
  palClearPad(GPIOF, GPIOF_STAT3);
}

static void set_green (PWMDriver *pwmd){
  (void) pwmd;
  palSetPad(GPIOF, GPIOF_STAT1);
}

static void set_orange (PWMDriver *pwmd){
  (void) pwmd;
  palSetPad(GPIOF, GPIOF_STAT2);
}

static void set_red (PWMDriver *pwmd){
  (void) pwmd;
  palSetPad(GPIOF, GPIOF_STAT3);
}

static PWMConfig pwmcfg = {
  200000,
  4096,
  clear_all,
  {
    {PWM_OUTPUT_DISABLED, set_green},
    {PWM_OUTPUT_DISABLED, set_orange},
    {PWM_OUTPUT_DISABLED, set_red},
    {PWM_OUTPUT_DISABLED, NULL},
  },
  0,
  0
};


/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS   1

/* Depth of the conversion buffer, channels are sampled four times each.*/
#define ADC_GRP1_BUF_DEPTH      1


static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

static const ADCConversionGroup adcgrpcfg = {
  FALSE,
  ADC_GRP1_NUM_CHANNELS,
  NULL,
  NULL,
  /* HW dependent part.*/
  0,
  ADC_CR2_SWSTART,
  ADC_SMPR1_SMP_AN10(ADC_SAMPLE_480),
  0,
  ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
  0,
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10)
};


    

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *arg) {
  (void)arg;
  chRegSetThreadName("blinker");
  while(TRUE){
    adcConvert(&ADCD1, &adcgrpcfg, samples, 1);
    pwmEnableChannel(&PWMD4, 0, samples[0]);
    chThdSleepMilliseconds(10);
  }
  return 0;

}

/*
static WORKING_AREA(waThread2, 128);
static msg_t Thread2(void *arg) {
  (void)arg;
  chRegSetThreadName("adc");
  while(TRUE){
    adcConvert(&ADCD1, &adcgrpcfg, samples, 1);
    chThdSleepMilliseconds(100);
  }
  return 0;

  }
*/

/*
 * Application entry point.
 */
int main(void) {
  halInit();
  chSysInit();
  pwmStart(&PWMD4, &pwmcfg);

  // Mise en marche de l'ADC 
  adcStart(&ADCD1,NULL);

  // Acquisition via l'ADC
   
  /*
   * Activates the serial driver 6 using the driver default configuration.
   */
  sdStart(&SD6, NULL);

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (TRUE) {
    chThdSleepMilliseconds(500);
  }
}
