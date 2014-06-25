#ifndef _THREAD
#define THREAD

#include <stdint.h>

//Definitions section
//Common
#define HEART_FLASH 0
#define ANIMATION1  1
#define ANIMATION2  2
//Master
#define PRESENCE_CHECK_TIME_MILLISECONDS 100

/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS   1

/* Depth of the conversion buffer, channel is sampled once.*/
#define ADC_GRP1_BUF_DEPTH      1

//Start Thread Fonctions Section
void startAdcThread(void);
void startPirThread(void);
void startHeartBeatThread(void);
void startLedThread(void);
void startRFThread(void);

//Miscellaneous
uint8_t nextSequence(void);

//Shared variables section
extern adcsample_t adc_samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];
extern BaseSequentialStream *chp;
extern volatile bool run_led_thread;
extern volatile uint16_t heart_beat_speed;
extern volatile bool presence_detected;
extern uint8_t RxBuf[32];
extern uint8_t TxBuf[32];

#endif
