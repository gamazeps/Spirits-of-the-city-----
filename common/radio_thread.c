#include "ch.h"
#include "hal.h"
#include "RF.h"
#include "radio_thread.h"
#include "debug.h"

static const EXTConfig extconfig={
  {
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
    {EXT_CH_MODE_FALLING_EDGE | EXT_MODE_GPIOA | EXT_CH_MODE_AUTOSTART, irq_handler},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL}
  },
};

void startRF(void){
  extStart(&EXTD1, &extconfig);
  // Init SPI
  static SPIConfig spi2cfg = {
    NULL, // No callback
    /* HW dependent part.*/
    GPIOB, // CS is PB12
    12,// CS is PB12
    0x00000038, // CR1 : clock as low as possible 5:3=111
  };

  // Get the SPI out of the "low power state"
  spiStart(&SPID2, &spi2cfg);

  // Configure the RF device
  ConfigureRF(SIZEPKT);
  switchOff();
  // Clean the RX FIFO
  ExecuteCommand(FLUSH_RX);
  WriteRegisterByte(STATUS, RX_DR);
}
