#ifndef ADC_THREAD_H
#define ADC_THREAD_H

#include <stdint.h>

//Start Thread Fonctions Section
void startAdcThread(void);

/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS   1

/* Depth of the conversion buffer, channel is sampled once.*/
#define ADC_GRP1_BUF_DEPTH      1

extern adcsample_t adc_samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

#endif
