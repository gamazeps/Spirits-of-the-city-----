/* Definition of animation 1 :
 - The father wake up : his heart beats faster and faster ; his head glows more and more ; his eyes lights up slowly in green
 - The children's eyes turn up at the same moment, in green.
 - The children heart beats faster and faster
 - All the heart slow down and the eyes slowly turn off
 */

#include "ch.h"
#include "hal.h"
#include "led.h"
#include "gamma.h"
#include "hsv2rgb.h"
#include "animation1.h"


void animation_1(){
  static uint8_t h = 0;
  static uint8_t s = 255;
  static uint8_t v = 0;
  static int delta_v = 1;  
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


void animation_2 (int8_t nb_beats, int8_t small_colour, int8_t big_colour){
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



 
