#ifndef LED_THREAD_H
#define LED_THREAD_H

// Définit si une animation doit etre en cours ou non
extern volatile bool run_led_thread;

void startLedThread(void);

#endif
