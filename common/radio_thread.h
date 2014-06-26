#ifndef RADIO_THREAD_H
#define RADIO_THREAD_H

// Buffers d'émission et réception
extern volatile uint8_t rxbuf[32];
extern volatile uint8_t txbuf[32];

void startRFThread(void);

#endif
