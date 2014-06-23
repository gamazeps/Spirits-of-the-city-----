#include "ch.h"
#include "hal.h"
#include "led.h"
#include "gamma.h"

// Set the big eye led to the desired color
void set_big_led(uint8_t r, uint8_t g, uint8_t b)
{
  pwmEnableChannel(&PWMD3, 3, led_gamma[r]);
  pwmEnableChannel(&PWMD3, 1, led_gamma[g]);
  pwmEnableChannel(&PWMD3, 2, led_gamma[b]);
}


// Set the small eye led to the desired color
void set_small_led(uint8_t r, uint8_t g, uint8_t b)
{
  pwmEnableChannel(&PWMD3, 0, led_gamma[r]);
  pwmEnableChannel(&PWMD2, 1, led_gamma[g]);
  pwmEnableChannel(&PWMD2, 0, led_gamma[b]);
}
