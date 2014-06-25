#ifndef RADIO_THREAD_H
#define RADIO_THREAD_H

// Buffers d'émission et réception
extern uint8_t RxBuf[32];
extern uint8_t TxBuf[32];

void startRFThread(void);

#endif
