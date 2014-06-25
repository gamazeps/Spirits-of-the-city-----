#include "ch.h"
#include "hal.h"
#include "led.h"
#include "gamma.h"
#include "hsv2rgb.h"

int heart_beat_speed = 60000; //speed of heart beat

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

//Set continiuously de big eye from a color to another (in a defined time)
void change_big_led_rgb (uint8_t r_start,uint8_t g_start,uint8_t b_start,uint8_t r_final,uint8_t g_final,uint8_t b_final, int time)
{
  uint8_t r, g, b = 0;
  int t = time/256;
  for (int i = 0; i < 256; i++)
    {
      r  = r_start + (r_start - r_final)*i/256;
      g  = g_start + (g_start - g_final)*i/256;
      b  = b_start + (b_start - b_final)*i/256;

      set_big_led_rgb (r, g, b);
      chThdSleepMilliseconds(t);
    }
}


//Set continiuously de small eye from a color to another (in a defined time)
void change_small_led_rgb (uint8_t r_start,uint8_t g_start,uint8_t b_start,uint8_t r_final,uint8_t g_final,uint8_t b_final, int time)
{
  uint8_t r, g, b = 0;
  int t = time/256;
  for (int i = 0; i < 256; i++)
    {
      r  = r_start + (r_start - r_final)*i/256;
      g  = g_start + (g_start - g_final)*i/256;
      b  = b_start + (b_start - b_final)*i/256;

      set_small_led_rgb (r, g, b);
      chThdSleepMilliseconds(t);
    }
}

//Set the heart beat at the desired speed
void set_heart_beat_speed (int speed)
{
  heart_beat_speed = speed;
}

// Change continiously the heart beat from a speed to another (in a defined time)
void change_heart_beat_speed (int initial_speed, int final_speed, int time)
{
  int diff = final_speed - initial_speed;
  diff = diff > 0 ? diff : -diff;
  int t = time/diff;
  int j = 0;
  for (int i = 0; i < diff; i++)
    {
      j = initial_speed + ((final_speed - initial_speed)*i/diff);
      set_heart_beat_speed (j);
      chThdSleepMilliseconds(t);
    }
}
