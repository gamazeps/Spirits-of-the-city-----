#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"
#include "thread.h"

// ADC - Luminosity sensor thread
static WORKING_AREA(waADCThread,128);

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
    adcConvert(&ADCD1, &adcgrpcfg, adc_samples, 1);

    //Sleep for 30 minutes
    chThdSleepMilliseconds(1800000);
  }
}

void startAdcThread(void){
  chThdCreateStatic(waADCThread, sizeof(waADCThread), NORMALPRIO, ADCThread, NULL);
}
