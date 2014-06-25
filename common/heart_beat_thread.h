#ifndef HEART_BEAT_THREAD_H
#define HEART_BEAT_THREAD_H

// Rythme cardiaque en 10ème de seconde
extern volatile uint16_t heart_beat_speed;

void startHeartBeatThread(void);

#endif
