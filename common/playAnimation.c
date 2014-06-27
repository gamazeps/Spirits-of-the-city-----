#include "playAnimation.h"
#include "led.h"

void playAnimation(void)
{
  switch(rxbuf[0])
    {
    case 0x0:
      animation_0();
      break;
    case 0x1:
      animation_1(rxbuf[1], rxbuf[2], rxbuf[3]);
      break;
    case 0x2:
      animation_2(rxbuf[1], rxbuf[2], rxbuf[3]);
      break;
    case 0x3:
      animation_3(rxbuf[1]);
      break;
    case 0x4:
      animation_4(rxbuf[1]);
      break;
    case 0x5:
      animation_5();
      break;
    case 0x6:
      animation_6();
      break;
    case 0x7:
      animation_7();
      break;
    default:;

    }
  flash_head();
}
