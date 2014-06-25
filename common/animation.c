
#include "ch.h"
#include "hal.h"
#include "led.h"
#include "chprintf.h"
#include "animation.h"

void animation_1(){
  static uint8_t h = 0;
  static uint8_t s = 255;
  static uint8_t v = 0;
  static uint8_t delta_v = 1;
  for(h=0;h<255;h++){
    v = v+delta_v;
    if (v==80)
      delta_v = -1;
    else if (v==0)
      delta_v = 1;
    set_heart_beat_speed(1000);
    set_big_led_hsv(h, s, v);
    set_small_led_hsv((h+128)%256, s, 80-v);
    chThdSleepMilliseconds(10);
  }
  set_big_led_hsv(0, 0, 0);
  set_small_led_hsv(0, 0, 0);

}


void animation_2 (uint8_t nb_beats, uint8_t small_colour, uint8_t big_colour){
  set_small_led_hsv(small_colour,255,80);
  set_big_led_hsv(big_colour,255,80);
  for(int8_t i=0;i<nb_beats; i++){
    set_small_uv_led (255);
    set_big_uv_led(255);
    chThdSleepMilliseconds(300);
    set_big_uv_led(0);
    chThdSleepMilliseconds(50);
    set_big_uv_led(255);
    chThdSleepMilliseconds(300);
    set_big_uv_led(0);
    chThdSleepSeconds(3);
  }
  set_small_led_hsv(0,0,0);
  set_big_led_hsv(0,0,0);
  set_small_uv_led(0);
  set_big_uv_led(0);
}

void animation_3 (uint8_t decalage, uint8_t color1, uint8_t color2 )
{
  chThdSleepMilliseconds(decalage*10+1);
  set_big_led_rgb (0,255,0);
  set_small_led_rgb (0,255,0);
  chThdSleepMilliseconds(2000-(decalage*10));
  set_big_led_rgb (0,0,0);
  set_small_led_rgb (0,0,0);
  change_heart_beat_speed(60000,1000,3000);
  set_small_uv_led(255);
  chThdSleepMilliseconds(400);
  set_small_uv_led(0);

  chThdSleepMilliseconds(decalage*10+1);
  for (uint8_t i =0; i<200;i+=8)
    {
      set_big_led_hsv(color1,255,80);
      chThdSleepMilliseconds(250-i);
      set_small_led_hsv(color2,255,80);
      chThdSleepMilliseconds(250-i);
      set_big_led_hsv(color1,0,0);
      chThdSleepMilliseconds(250-i);
      set_small_led_hsv(color2,0,0);
      chThdSleepMilliseconds(250-i);
    }

  chThdSleepMilliseconds(2000-decalage*10);

  for (uint8_t i =0; i<200;i+=8)
    {
      set_big_led_hsv(color1,255,80);
      set_small_led_hsv(color2,255,80);
      chThdSleepMilliseconds(250-i);
      set_big_led_hsv(color2,255,80);
      set_small_led_hsv(color1,255,80);
      chThdSleepMilliseconds(250-i);
    }
  set_small_uv_led(255);
  chThdSleepMilliseconds(200);
  set_small_uv_led(0);

  for (uint8_t i =0; i<254;i++)
    {
      set_big_led_rgb(0,255-i,0);
      set_small_led_rgb(0,255-i,0);
      chThdSleepMilliseconds(10);
    }

  change_heart_beat_speed(1000,60000,3000);
}
