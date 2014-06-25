#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "hsv2rgb.h"
#include "led.h"
#include "thread.h"

static WORKING_AREA(waHeartbeatThread, 128);
__attribute__((__noreturn__))  static msg_t HeartbeatThread(void *arg) {
  (void)arg;
  chRegSetThreadName("Heartbeat");
  while(TRUE) {
    set_big_uv_led(0);
    chThdSleepMilliseconds(heart_beat_speed/2);
    set_big_uv_led(128);
    chThdSleepMilliseconds(heart_beat_speed/4);
    set_big_uv_led(0);
    chThdSleepMilliseconds(heart_beat_speed/8);
    set_big_uv_led(128);
    chThdSleepMilliseconds(heart_beat_speed/8);
  }
}
void startHeartBeatThread(void){
  chThdCreateStatic(waHeartbeatThread, sizeof(waHeartbeatThread), NORMALPRIO, HeartbeatThread, NULL);
}
