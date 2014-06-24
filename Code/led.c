#include "ch.h"
#include "hal.h"
#include "led.h"
#include "gamma.h"
#include "hsv2rgb.h"

// Set the big eye led to the desired color
void set_big_led_rgb(uint8_t r, uint8_t g, uint8_t b)
{
  pwmEnableChannel(&PWMD3, 3, led_gamma[r]);
  pwmEnableChannel(&PWMD3, 1, led_gamma[g]);
  pwmEnableChannel(&PWMD3, 2, led_gamma[b]);
}

void set_big_led_hsv(uint8_t h, uint8_t s, uint8_t v)
{
  static hsv_color hsv = {0, 0, 0};
  static rgb_color rgb;
  hsv.h = h; hsv.s = s; hsv.v = v;
  rgb = hsv2rgb(hsv);
  set_big_led_rgb(rgb.r, rgb.g, rgb.b);
}


// Set the small eye led to the desired color
void set_small_led_rgb(uint8_t r, uint8_t g, uint8_t b)
{
  pwmEnableChannel(&PWMD3, 0, led_gamma[r]);
  pwmEnableChannel(&PWMD2, 1, led_gamma[g]);
  pwmEnableChannel(&PWMD2, 0, led_gamma[b]);
}

void set_small_led_hsv(uint8_t h, uint8_t s, uint8_t v)
{
  static hsv_color hsv = {0, 0, 0};
  static rgb_color rgb;
  hsv.h = h; hsv.s = s; hsv.v = v;
  rgb = hsv2rgb(hsv);
  set_small_led_rgb(rgb.r, rgb.g, rgb.b);
}

// Set the big UV LED to the desired intensity
void set_big_uv_led(uint8_t val)
{
  pwmEnableChannel(&PWMD2, 2, led_gamma[val]);
}

// Set the small UV LED to the desired intensity
void set_small_uv_led(uint8_t val)
{
  pwmEnableChannel(&PWMD2, 3, led_gamma[val]);
}
