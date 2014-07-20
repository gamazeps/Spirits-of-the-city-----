#include "ch.h"
#include "hal.h"
#include "leds.h"
#include "gamma.h"
#include "hsv2rgb.h"

static SEMAPHORE_DECL(hb_sem, 0);

static int hb_delay;
static int beating;

// PWM configuration for PWMD2 and PWMD3
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

// Heart beat thread
static WORKING_AREA(HEART_BEAT_WA, 128);
static __attribute__((noreturn)) msg_t heart_beat_thread(void *arg){
	(void) arg;
  while(1){
    while(beating){
      set_small_uv_led(255);
      chThdSleepMilliseconds(200);
      set_small_uv_led(0);
      chThdSleepMilliseconds(200);
      set_small_uv_led(255);
      chThdSleepMilliseconds(200);
      set_small_uv_led(0);
      chThdSleepMilliseconds(hb_delay);
    }
    chSemWait(&hb_sem);
	}
}

void leds_init(void) {
  pwmStart(&PWMD2, &pwmcfg);
  pwmStart(&PWMD3, &pwmcfg);
  set_heart_beat_speed(0);
  chThdCreateStatic(HEART_BEAT_WA, sizeof(HEART_BEAT_WA), NORMALPRIO,
      heart_beat_thread, NULL);
}

void set_big_led_rgb(rgb_color color){
  pwmEnableChannel(&PWMD3, 3, led_gamma[color.r]);
  pwmEnableChannel(&PWMD3, 1, led_gamma[color.g]);
  pwmEnableChannel(&PWMD3, 2, led_gamma[color.b]);
}

void set_small_led_rgb(rgb_color color){
  pwmEnableChannel(&PWMD3, 0, led_gamma[color.r]);
  pwmEnableChannel(&PWMD2, 1, led_gamma[color.g]);
  pwmEnableChannel(&PWMD2, 0, led_gamma[color.b]);
}

void set_big_led_hsv(hsv_color color){
  static rgb_color rgb;
  rgb = hsv2rgb(color);
  set_big_led_rgb(rgb);
}

void set_small_led_hsv(hsv_color color){
  static rgb_color rgb;
  rgb = hsv2rgb(color);
  set_small_led_rgb(rgb);
}

// Head LED
void set_big_uv_led(uint8_t val){
  if (val) pwmEnableChannel(&PWMD2, 3, led_gamma[val]);
  else pwmDisableChannel(&PWMD2, 3);
}

// Heart LED
void set_small_uv_led(uint8_t val){
  if (val) pwmEnableChannel(&PWMD2, 2, led_gamma[val]);
  else pwmDisableChannel(&PWMD2, 2);
}

// Speed in bpm
void set_heart_beat_speed(int speed) {
  if(speed){
    hb_delay = (60 * 1000 - 600) / speed; 
    if(!beating){
      beating = 1;
      chSemSignal(&hb_sem);
    }
  } else {
    hb_delay = 1;
    beating = 0;
  }
}

void flash_head(void) {
  set_big_uv_led(255);
  chThdSleepMilliseconds(100);
  set_big_uv_led(0);
  chThdSleepMilliseconds(100);
  set_big_uv_led(255);
  chThdSleepMilliseconds(100);
  set_big_uv_led(0);
  chThdSleepMilliseconds(100);
}

