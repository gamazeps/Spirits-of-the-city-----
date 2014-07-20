//FIXME deal with the ISTRANSMITTER bs, and update architecture
#include "ch.h"
#include "hal.h"
#include "radio_thread.h"
#include "leds.h"
#include "lfsr.h"
#include "debug.h"
#include <string.h>

#define PRIM_RX (1 << 0)
#define PWR_UP  (1 << 1)
#define CRCO    (1 << 2)
#define EN_CRC  (1 << 3)

static SEMAPHORE_DECL(sem, 0);

uint8_t rxbuf[SIZEPKT] = {0};
uint8_t txbuf[SIZEPKT] = {0};

static void switch_on(void);
static void switch_off(void);
static void set_CE(int on);
static void register_write_bytes(int register_id, int nb_bytes, uint8_t* wtxbuf);
static void register_write_byte(int register_id, uint8_t value);
static void execute_command(int command);
static void radio_configure(int sizepck);
static void irq_handler(EXTDriver *e, expchannel_t c);

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

// Init SPI
static SPIConfig radio_spi_cfg = {
  NULL, // No callback
  /* HW dependent part.*/
  GPIOB, // CS is PB12
  12,// CS is PB12
  0x00000038, // CR1 : clock as low as possible 5:3=111
};

void radio_init(void){
  // Init
  extStart(&EXTD1, &extconfig);
  // Get the SPI out of the "low power state"
  spiStart(&SPID2, &radio_spi_cfg);
  // Configure the RF device
  radio_configure(SIZEPKT);
  switch_off();
  // Clean the RX FIFO
  execute_command(FLUSH_RX);
  register_write_byte(STATUS, RX_DR);
}

static void switch_on(void){
  uint8_t conf = (EN_CRC | CRCO | PWR_UP);
  conf |= ISTRANSMITTER ? 0 : PRIM_RX;
  register_write_byte(CONFIG, conf);
}

static void switch_off(void){
  uint8_t conf = (EN_CRC | CRCO);
  conf |= ISTRANSMITTER ? 0 : PRIM_RX;
  regsiter_write_byte(CONFIG, conf);
}

static void set_CE(int on){
  on ? palSetPad(GPIOB, GPIOB_RF_CE) : palClearPad(GPIOB, GPIOB_RF_CE);
}

/************************************************************************
 *    SPI related code                                                  *
 ***********************************************************************/

static void spi_start_transaction(void) {
  chThdSleepMilliseconds(1);
  spiSelect(&SPID2);
  chThdSleepMilliseconds(1);
}

static void spi_stop_transaction(void) {
  chThdSleepMilliseconds(1);
  spiUnselect(&SPID2);
  chThdSleepMilliseconds(1);
}

static void register_write_bytes(int register_id, int nb_bytes, uint8_t* wtxbuf){
  spi_start_transaction();
  uint8_t command = W_REGISTER(register_id);
  spiSend(&SPID2, 1, &command);
  spiSend(&SPID2, nb_bytes, wtxbuf);
  spi_stop_transaction();
}

static void register_write_byte(int register_id, uint8_t value) {
  register_write_bytes(register_id, 1, &value);
}

static void register_read_bytes(int register_id, int nb_bytes, uint8_t* rrxbuf ){
  uint8_t command = R_REGISTER(register_id);
  spi_start_transaction();
  spiSend(&SPID2, 1, &command);
  spiReceive(&SPID2, nb_bytes, rrxbuf);
  spi_stop_transaction();
}

static uint8_t register_read_byte(int register_id) {
  uint8_t value;
  register_read_bytes(register_id, 1, &value);
  return value;
}


/**********************************************************************
 *                                ^                                   *
 *                                ||                                  *
 *                               good                                 *
 *---------------------------------------------------------------------
 *                                bad                                 *
 *                                ||                                  *
 *                                V                                   *
 *********************************************************************/


static void execute_command(int command) {
  spi_start_transaction();
  spiSend(&SPID2, 1, &command);
  spi_stop_transaction();
}


//To send data to an other radio, puts the data int the TX_PAYLOAD
static void radio_send(const uint8_t* datasend, int numWords) {
  set_CE(0);
  spi_start_transaction();
  uint8_t command = W_TX_PAYLOAD;
  spiSend(&SPID2, 1, &command);
  spiSend(&SPID2, numWords, datasend);
  spi_stop_transaction();
  set_CE(1);
  chThdSleepMilliseconds(1);
  set_CE(0);
}

// Returns TRUE if a packet has been received
static int radio_receive(uint8_t *rrxbuf, size_t pkt_size, int timeout_ms) {
  set_CE(1);//sets CE to 1
  msg_t msgMode = chSemWaitTimeout(&sem, timeout_ms);
  if(msgMode == RDY_OK){
    set_CE(0);
    uint8_t command = R_RX_PAYLOAD;
    spi_start_transaction();
    spiSend(&SPID2, 1, &command);
    spiReceive(&SPID2, pkt_size, rrxbuf);
    spi_stop_transaction();
    register_write_byte(STATUS, RX_DR);
    return TRUE;
  }
  else if(msgMode == RDY_TIMEOUT) {
    set_CE(0);
  }
  return FALSE;
}

static void radio_configure(int sizepck) {
  //Configure the register 00 (config)
  switch_on();
  //Disable the auto-ACK
  register_write_byte(EN_AA, 0);
  //chosing channels
  register_write_byte(EN_RXADDR, 1);
  //Adress width (1 => 3 bytes)
  register_write_byte(SETUP_AW, 1);
  //set retransmission to 0
  register_write_byte(SETUP_RTR, 0);
  //set the number of channels used
  register_write_byte(RF_CH, 2);
  //??
  register_write_byte(RF_SETUP, 0x07);
  //setting the  adress and the payload width
  uint8_t addr[3] = {0xB1, 0xB2, 0xB3};
  if(ISTRANSMITTER) {
    register_write_bytes(TX_ADDR,3,addr);
  } else {
    register_write_bytes(RX_ADDR_P0, 3, addr);
    register_write_byte(RX_PW_P0, sizepck);
  }
}


void send_message(uint8_t* stxbuf) {
  switch_on();
  int t = chTimeNow();
  uint8_t i = 0;
  uint8_t j = 0;
  uint8_t color= lfsr() % 256;
  while((int) chTimeNow() < (int) (t + 6000)) {
    radio_send(stxbuf, SIZEPKT);
    j = (i < 80) ? i : 80-i;
    set_small_led_hsv(color, 255, j);
    set_big_led_hsv(color, 255, j);
    i = (i + 1) % 160;
  }
}

// Get the animation parameters in rxbuf and waits for the top if needed.
// Return TRUE if an animation is ready, 0 if not.
int receive_animation(void) {
  switch_on();
  static uint8_t rxbuf2[SIZEPKT] = {0};
  int needs_start = 0;
  int received;
  while (TRUE) {
    received = radio_receive(rxbuf2, SIZEPKT, needs_start ? 10000 : 1000);
    if (!received)
      break;
    if (rxbuf2[0] == 0xff) {
      if (needs_start) {
        break;
      } else {
      // Top has no meaning here
      continue;
      }
    }
    memcpy(rxbuf, rxbuf2, SIZEPKT);
    if ((rxbuf2[0] & 0x80) == 0) {
      needs_start = 1;
    } else {
      break;
    }
  }
  switch_off();
  return received;
}

void await_animation(void) {
  while (TRUE) {
    int received = receive_animation();
    if (received) {
      break;
    }
    chThdSleepSeconds(5);
  }
}

static void irq_handler(EXTDriver *e, expchannel_t c){
  (void) e;
  (void) c;
  chSysLockFromIsr();
  chSemSignalI(&sem);
  chSysUnlockFromIsr();
}

