#include <stdint.h>
#include "radio_thread.h"
#include "ch.h"
#include "hal.h"
#include "debug.h"
#include "chprintf.h"

//Those definitions need to be put in Radio Thread
uint8_t RxBuf[32];
uint8_t TxBuf[32];
