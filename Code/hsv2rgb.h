/* hsv2rgb.h
 * Convert Hue Saturation Value to Red Green Blue
 *
 * Programme de convertion d'une information HSV en RGB
 */
#ifndef HSV2RGB_H
#define HSV2RGB_H

#include <stdint.h>

typedef struct {
  uint8_t h;
  uint8_t s;
  uint8_t v;
} hsv_color;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

rgb_color hsv2rgb(hsv_color hsv);

#endif
