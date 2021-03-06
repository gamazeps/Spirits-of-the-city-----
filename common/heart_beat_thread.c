#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "led.h"
#include "heart_beat_thread.h"

volatile int heart_beat_speed = 600; //speed of heart beat in 10th of seconds

static WORKING_AREA(waHeartbeatThread, 128);
__attribute__((__noreturn__))  static msg_t HeartbeatThread(void *arg) {
  (void)arg;
  chRegSetThreadName("Heartbeat");
  while(TRUE) {
    set_small_uv_led(255);
    chThdSleepMilliseconds(200);
    set_small_uv_led(0);
    chThdSleepMilliseconds(200);
    set_small_uv_led(255);
    chThdSleepMilliseconds(200);
    set_small_uv_led(0);

    // Gget current time
    systime_t t = chTimeNow();
    while(chTimeNow() < (t+heart_beat_speed*100))
      chThdSleepMilliseconds(10);
  }
}
void startHeartBeatThread(void){
  chThdCreateStatic(waHeartbeatThread, sizeof(waHeartbeatThread), NORMALPRIO, HeartbeatThread, NULL);
}
