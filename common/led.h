#ifndef LED_H
#define LED_H

#include <stdint.h>

void set_big_led_rgb(uint8_t r, uint8_t g, uint8_t b);
void set_big_led_hsv(uint8_t h, uint8_t s, uint8_t v);
void set_small_led_rgb(uint8_t r, uint8_t g, uint8_t b);
void set_small_led_hsv(uint8_t h, uint8_t s, uint8_t v);
void set_big_uv_led(uint8_t val);
void set_small_uv_led(uint8_t val);
void change_big_led_rgb (uint8_t r_start,uint8_t g_start,uint8_t b_start,uint8_t r_final,uint8_t g_final,uint8_t b_final, int time);
void change_small_led_rgb (uint8_t r_start,uint8_t g_start,uint8_t b_start,uint8_t r_final,uint8_t g_final,uint8_t b_final, int time);
void set_heart_beat_speed (uint16_t speed);
void change_heart_beat_speed (int initial_speed, int final_speed, int time);

#endif
