#include "ch.h"
#include "hal.h"
#include "leds.h"
#include "hsv2rgb.h"
#include "pir.h"

int main(void) {
  // Initialize system
  halInit();
  chSysInit();

  leds_init();
  pir_init(NORMALPRIO);

  hsv_color color = {81, 255, 255};

  while (1) {
    chThdSleepMilliseconds(20);
    set_big_led_hsv(color);
  }

}
