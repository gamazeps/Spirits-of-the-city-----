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

// Heartbeat thread
static WORKING_AREA(waHBT, 128);
__attribute__((__noreturn__))  static msg_t HBT(void *arg) {
  (void)arg;
  chRegSetThreadName("Heart Beat");
  static uint8_t h = 0;
  static uint8_t s = 255;
  static uint8_t v = 0;
  static int delta_v = 1;
  static hsv_color hsv = {0, 0, 0};
  static rgb_color rgb;
  while (TRUE) {
    h += 1;
    v = v+delta_v;
    if (v==80)
      delta_v = -1;
    else if (v==0)
      delta_v = 1;

    hsv.h = h; hsv.s = s; hsv.v = v;
    rgb = hsv2rgb(hsv);
    set_big_led(rgb.r, rgb.g, rgb.b);

    hsv.h = (h+100)%256; hsv.s = s; hsv.v = v;
    rgb = hsv2rgb(hsv);
    set_small_led(rgb.r, rgb.g, rgb.b);

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
