#include <stdint.h>
#include "lfsr.h"

uint16_t lfsr(void){
  static uint16_t lfsr = 0xACE1;

  /* taps: 16 5 4 3; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
  uint8_t bit  = ((lfsr >> 0) ^ (lfsr >> 11) ^ (lfsr >> 12) ^ (lfsr >> 13) ) & 1;
  lfsr =  (lfsr >> 1) | (bit << 15);

  return lfsr;
}

