#include "ch.h"
#include "hal.h"
#include "pir.h"

/* Semaphor and event declarations used to debounce the PIR */
static SEMAPHORE_DECL(pir_sem, 1);
EVENTSOURCE_DECL(pir);

/* Triggered when there is a rising edge on PC13 */
static void extcb(EXTDriver *extp, expchannel_t channel) {
	(void)extp;
	chSysLockFromIsr();
	if(channel==13)
		chSemSignalI(&pir_sem);
	chSysUnlockFromIsr();
}

/* 
 * Debounce thread for the PIR, might be overkill but the processor 
 * can handle it (and this is an educational project, so the more 
 * concepts there are, the better
*/
static WORKING_AREA(PIR_WA, 32);
static __attribute__((noreturn)) msg_t pirThread(void *arg){
	(void) arg;
	while(1){
		// main loop
		chSemWait(&pir_sem);
		chThdSleepMilliseconds(15);
		if(palReadPad(GPIOC, GPIOC_PROXSENSOR))
			chEvtBroadcast(&pir);
	}
}

/* Listening to the rising edge on PC13 */
static const EXTConfig extcfg = {
	{
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_RISING_EDGE | EXT_MODE_GPIOC, extcb},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL}
	}
};

void pir_init(tprio_t prio){
	extInit();
	extStart(&EXTD1, &extcfg);
	extChannelEnable(&EXTD1, 13);
	chThdCreateStatic(&PIR_WA, sizeof(PIR_WA),
      prio, pirThread, NULL);
}

