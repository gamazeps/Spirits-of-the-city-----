
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
  for(h=0; h<255; h++){
    v = v + delta_v;
    if (v==80)
      delta_v = -1;
    else if (v==0)
      delta_v = 1;

    set_big_led_hsv(h, s, v);
    set_small_led_hsv((h+128)%256, s, 80-v);

    set_heart_beat_speed(10);

    chThdSleepMilliseconds(10);
  }

  // Turn off eyes
  set_big_led_hsv(0, 0, 0);
  set_small_led_hsv(0, 0, 0);

  // Return to pace
  set_heart_beat_speed(600);
}


void animation_2 (int delay, uint8_t small_colour, uint8_t big_colour){
  // Set eyes to the given colors
  set_small_led_hsv(small_colour, 255, 80);
  set_big_led_hsv(big_colour, 255, 80);

  // make heart explode
  set_heart_beat_speed(3);

  // wait some time
  chThdSleepMilliseconds(delay*100);

  // Close eyes
  set_small_led_hsv(0,0,0);
  set_big_led_hsv(0,0,0);
  set_small_uv_led(0);

  // Return to pace
  set_heart_beat_speed(600);
}

void animation_3 (uint8_t decalage, uint8_t color1, uint8_t color2 )
{
  // Wait for the specified time
  chThdSleepMilliseconds(decalage*10+1);

  // Set eyes to green
  set_big_led_rgb (0,255,0);
  set_small_led_rgb (0,255,0);

  // Recover phase and shut down eyes
  chThdSleepMilliseconds(2000-(decalage*10));
  set_big_led_rgb (0,0,0);
  set_small_led_rgb (0,0,0);

  // Make heart speed up
  set_heart_beat_speed(3);

  // Flash head
  flash_head();

  chThdSleepMilliseconds(decalage*10+1);
  for (int i =0; i<200; i+=8) {
    set_big_led_hsv(color1, 255, 80);
    chThdSleepMilliseconds(250-i);

    set_small_led_hsv(color2, 255, 80);
    chThdSleepMilliseconds(250-i);

    set_big_led_hsv(0, 0, 0);
    chThdSleepMilliseconds(250-i);

    set_small_led_hsv(0, 0, 0);
    chThdSleepMilliseconds(250-i);
  }

  chThdSleepMilliseconds(2000-decalage*10);

  for (int i =0; i<200;i+=8) {
    set_big_led_hsv(color1, 255, 80);
    set_small_led_hsv(color2, 255, 80);
    chThdSleepMilliseconds(250-i);

    set_big_led_hsv(color2, 255, 80);
    set_small_led_hsv(color1, 255, 80);
    chThdSleepMilliseconds(250-i);
  }

  flash_head();

  for (int i =0; i<256; i++) {
    set_big_led_rgb(0, 255-i, 0);
    set_small_led_rgb(0, 255-i, 0);
    chThdSleepMilliseconds(10);
  }

  // Go to pace
  set_heart_beat_speed(600);
}
