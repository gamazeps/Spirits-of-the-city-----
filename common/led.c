#include "ch.h"
#include "hal.h"
#include "led.h"
#include "chprintf.h"
#include "gamma.h"
#include "hsv2rgb.h"
#include "heart_beat_thread.h"
#include <stdint.h>

// Configuration des PWM pour les LED
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


void led_init(void) {
  // Initializes the PWM driver 3 and 4. Output are routed to LEDs in board.h
  pwmStart(&PWMD2, &pwmcfg);
  pwmStart(&PWMD3, &pwmcfg);
}


// Set the big eye led to the desired color
void set_big_led_rgb(uint8_t r, uint8_t g, uint8_t b){
  pwmEnableChannel(&PWMD3, 3, led_gamma[r]);
  pwmEnableChannel(&PWMD3, 1, led_gamma[g]);
  pwmEnableChannel(&PWMD3, 2, led_gamma[b]);
}


void set_big_led_hsv(uint8_t h, uint8_t s, uint8_t v){
  static hsv_color hsv = {0, 0, 0};
  static rgb_color rgb;
  hsv.h = h; hsv.s = s; hsv.v = v;
  rgb = hsv2rgb(hsv);
  set_big_led_rgb(rgb.r, rgb.g, rgb.b);
}


// Set the small eye led to the desired color
void set_small_led_rgb(uint8_t r, uint8_t g, uint8_t b){
  pwmEnableChannel(&PWMD3, 0, led_gamma[r]);
  pwmEnableChannel(&PWMD2, 1, led_gamma[g]);
  pwmEnableChannel(&PWMD2, 0, led_gamma[b]);
}


void set_small_led_hsv(uint8_t h, uint8_t s, uint8_t v){
  static hsv_color hsv = {0, 0, 0};
  static rgb_color rgb;
  hsv.h = h; hsv.s = s; hsv.v = v;
  rgb = hsv2rgb(hsv);
  set_small_led_rgb(rgb.r, rgb.g, rgb.b);
}


// Set the big UV LED to the desired intensity
void set_big_uv_led(uint8_t val){
  pwmEnableChannel(&PWMD2, 3, led_gamma[val]);
}


// Set the small UV LED to the desired intensity
void set_small_uv_led(uint8_t val){
  pwmEnableChannel(&PWMD2, 2, led_gamma[val]);
}

void set_heart_beat_speed(int speed) {
  heart_beat_speed = speed;
}

// Change continiously the heart beat from a speed to another (in a defined time)
void change_heart_beat_speed (int final_speed, int time){
  static int initial_speed;
  initial_speed = heart_beat_speed;
  int diff = final_speed - initial_speed;
  int j = 0;
  for (int i = 0; i < 100; i++)
    {
      j = initial_speed + ((diff)*i/100);
      heart_beat_speed = j;
      chThdSleepMilliseconds(time/100);
    }
}
