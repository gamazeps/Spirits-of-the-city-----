#ifndef LED_H
#define LED_H

#include <stdint.h>

void led_init(void);
void set_big_led_rgb(uint8_t r, uint8_t g, uint8_t b);
void set_big_led_hsv(uint8_t h, uint8_t s, uint8_t v);
void set_small_led_rgb(uint8_t r, uint8_t g, uint8_t b);
void set_small_led_hsv(uint8_t h, uint8_t s, uint8_t v);
void set_big_uv_led(uint8_t val);
void set_small_uv_led(uint8_t val);
void set_heart_beat_speed(int speed);
void flash_head(void);

#endif
