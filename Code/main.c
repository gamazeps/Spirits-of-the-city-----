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

/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS   1

/* Depth of the conversion buffer, channels are sampled four times each.*/
#define ADC_GRP1_BUF_DEPTH      1

// Debug channel
BaseSequentialStream *chp =  (BaseSequentialStream *)&SD1;

static adcsample_t adc_samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

static const ADCConversionGroup adcgrpcfg = {
  FALSE,
  ADC_GRP1_NUM_CHANNELS,
  NULL,
  NULL,
  /* HW dependent part.*/

  //CR1 && CR2 Init
  0,
  ADC_CR2_SWSTART,

  //SMPRX Init
  0,
  0,
  ADC_SMPR3_SMP_AN0(ADC_SAMPLE_384),

  //SQRX Init
  ADC_SQR5_SQ1_N(ADC_CHANNEL_IN0),
  0,
  0,
  0,
  ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS)
};


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

// LED thread
static volatile bool run_led_thread = FALSE;
static WORKING_AREA(waLEDThread, 128);
__attribute__((__noreturn__))  static msg_t LEDThread(void *arg) {
  (void)arg;
  chRegSetThreadName("LED");
  static uint8_t h = 0;
  static uint8_t s = 255;
  static uint8_t v = 0;
  static int delta_v = 1;
  while (TRUE) {
    if(run_led_thread) {
      h += 1;
      v = v+delta_v;
      if (v==80)
        delta_v = -1;
      else if (v==0)
        delta_v = 1;

      set_big_led_hsv(h, s, v);
      set_small_led_hsv((h+128)%256, s, 80-v);
    }
    else {
      set_big_led_hsv(0, 0, 0);
      set_small_led_hsv(0, 0, 0);
    }

    chThdSleepMilliseconds(10);
  }
}

// Heart beat thread
static WORKING_AREA(waHeartbeatThread, 128);
__attribute__((__noreturn__))  static msg_t HeartbeatThread(void *arg) {
  (void)arg;
  chRegSetThreadName("Heartbeat");
  while(TRUE) {
    set_big_uv_led(0);
    chThdSleepMilliseconds(heart_beat_speed/2);
    set_big_uv_led(128);
    chThdSleepMilliseconds(heart_beat_speed/4);
    set_big_uv_led(0);
    chThdSleepMilliseconds(heart_beat_speed/8);
    set_big_uv_led(128);
    chThdSleepMilliseconds(heart_beat_speed/8);
  }
}

// PIR sensor thread
static WORKING_AREA(waPIRThread, 128);
__attribute__((__noreturn__))  static msg_t PIRThread(void *arg) {
  (void)arg;
  chRegSetThreadName("PIR");
  while(TRUE) {
    if (palReadPad(GPIOC, GPIOC_PROXSENSOR)==PAL_HIGH) {
      run_led_thread = TRUE;
      chThdSleepSeconds(5);
      run_led_thread = FALSE;
    }
    chThdSleepMilliseconds(100);
  }
}

// ADC - Luminosity sensor thread
static WORKING_AREA(waADCThread,128);
__attribute__((__noreturn__)) static msg_t ADCThread(void *arg){
  (void) arg;
  chRegSetThreadName("ADC");
  while(TRUE){
    adcConvert(&ADCD1, &adcgrpcfg, adc_samples, 1);

    //Sleep for 30 minutes
    chThdSleepMilliseconds(1800000);
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

  // Activate ADC
  adcStart(&ADCD1,NULL);

  // Initializes the PWM driver 3 and 4. Output are routed to LEDs in board.h
  pwmStart(&PWMD2, &pwmcfg);
  pwmStart(&PWMD3, &pwmcfg);

  // Launch the LED thread
  chThdCreateStatic(waLEDThread, sizeof(waLEDThread), NORMALPRIO, LEDThread, NULL);

  // Launch the heart beat thread
  chThdCreateStatic(waHeartbeatThread, sizeof(waHeartbeatThread), NORMALPRIO, HeartbeatThread, NULL);

  //Launch ADC Thread
  chThdCreateStatic(waADCThread, sizeof(waADCThread), NORMALPRIO, ADCThread, NULL);
  // Launch PIR thread
  chThdCreateStatic(waPIRThread, sizeof(waPIRThread), NORMALPRIO, PIRThread, NULL);

  // Output some things on the serial port but mainly sleep
  while (TRUE) {
    chprintf(chp, "Hello World!\r\n");
    chThdSleepSeconds(1);
  }
}
