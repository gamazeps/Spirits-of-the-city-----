#ifndef LEDS_H
#define LEDS_H

#include "hsv2rgb.h"

void leds_init(void); 
void set_big_led_rgb(rgb_color color);
void set_small_led_rgb(rgb_color color);
void set_big_led_hsv(hsv_color color);
void set_small_led_hsv(hsv_color color);
void set_big_uv_led(uint8_t val);
void set_small_uv_led(uint8_t val);
void set_heart_beat_speed(int speed);
void flash_head(void);
  
#endif

