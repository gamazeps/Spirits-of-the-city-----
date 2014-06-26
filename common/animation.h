#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdint.h>

#define ANIMS_NUMBER 5

void animation_0(void);
void animation_1(int delay, uint8_t small_colour, uint8_t bit_colour);
void animation_2(uint8_t decalage, uint8_t color1, uint8_t color2);
void animation_3(uint8_t color);
void animation_4(uint8_t color);

#endif
