#ifndef RADIO_THREAD_H
#define RADIO_THREAD_H

#include "RF.h"

// Buffers d'émission et réception
extern uint8_t rxbuf[SIZEPKT];
extern uint8_t txbuf[SIZEPKT];

void startRF(void);

#endif
