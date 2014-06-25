#ifndef _THREAD
#define THREAD

//Start Thread Fonctions Section
void startAdcThread(void);
void startPirThread(void);
void startHeartBeatThread(void);
void startLedThread(void);

//Shared variables section

/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS   1

/* Depth of the conversion buffer, channels are sampled four times each.*/
#define ADC_GRP1_BUF_DEPTH      1

extern adcsample_t adc_samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];
extern BaseSequentialStream *chp;
extern volatile bool run_led_thread;

#endif
