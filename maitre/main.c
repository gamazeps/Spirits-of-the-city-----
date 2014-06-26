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
#include "debug.h"
#include "hsv2rgb.h"
#include "led.h"
#include "pir_thread.h"
#include "led_thread.h"
#include "heart_beat_thread.h"
#include "led_thread.h"
#include "adc_thread.h"
#include "radio_thread.h"
#include <stdint.h>
#include "lfsr.h"

// Debug channel
BaseSequentialStream *chp =  (BaseSequentialStream *)&SD1;

/*
 * Application entry point.
 */
int main(void) {
  // Initialize system
  halInit();
  chSysInit();

  // Activate USART1 using default configuration (115200 8N1)
  sdStart(&SD1, NULL);

  // Init LEDs
  led_init();

  // Launch the LED thread
  startLedThread();

  // Launch the heart beat thread
  startHeartBeatThread();

  //Launch ADC Thread
  startAdcThread();

  // Launch PIR thread
  startPirThread();

  // Launch RF thread
  //startRFThread();
  flash_head();

  // Output some things on the serial port but mainly sleep
  while (TRUE) {
    chThdSleepSeconds(1);
  }

}
