#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "adc_thread.h"

// ADC - Luminosity sensor thread
static WORKING_AREA(waADCThread,128);

volatile bool night = TRUE;

/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS   1
/* Depth of the conversion buffer, channel is sampled once.*/
#define ADC_GRP1_BUF_DEPTH      1

adcsample_t adc_samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

static const ADCConversionGroup adcgrpcfg = {
  FALSE,
  ADC_GRP1_NUM_CHANNELS,
  NULL,
  NULL,
  /* HW dependent part.*/

  //CR1 && CR2 Init
  0,
  ADC_CR2_SWSTART,

  //SMPRX Init
  0,
  0,
  ADC_SMPR3_SMP_AN0(ADC_SAMPLE_384),

  //SQRX Init
  ADC_SQR5_SQ1_N(ADC_CHANNEL_IN0),
  0,
  0,
  0,
  ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS)
};


__attribute__((__noreturn__)) static msg_t ADCThread(void *arg){
  (void) arg;
  chRegSetThreadName("ADC");
  while(TRUE){
    // Activate ADC
    adcStart(&ADCD1,NULL);
    chThdSleepMilliseconds(1);

    // Launch conversion
    adcConvert(&ADCD1, &adcgrpcfg, adc_samples, 1);

    // Stop ADC to save energy
    adcStop(&ADCD1);

    //Sleep for 30 minutes
    chThdSleepSeconds(1800);
  }
}

void startAdcThread(void){
  chThdCreateStatic(waADCThread, sizeof(waADCThread), NORMALPRIO, ADCThread, NULL);
}
