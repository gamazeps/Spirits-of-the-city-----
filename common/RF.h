#include "ch.h"
#include "hal.h"
#include "thread.h"

#define ISTRANSMITTER FALSE
//RF registers and function names
#define R_REGISTER(x) (x & 0x1F)
#define W_REGISTER(x) ((x & 0x1F) | 0x20)
#define NOP 0xff
#define R_RX_PAYLOAD 0x61
#define W_TX_PAYLOAD 0xA0
#define FLUSH_RX 0xE2
#define FLUSH_TX 0xE1

#define CONFIG 0x00
#define EN_AA 0x01
#define EN_RXADDR 0x02
#define SETUP_AW 0x03
#define SETUP_RTR 0x04
#define RF_CH 0x05
#define RF_SETUP 0x06
#define STATUS 0x07
//It doesn't seem relevant to use registers 08 and 09 in our situation,neither 0B to 0F
#define RX_ADDR_P0 0x0A
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define FIFO_STATUS 0x17
#define RX_EMPTY (1 << 0)
#define DYNP 0x1C
#define RX_DR (1 << 6)
#define SIZEPKT 3

void set_CE(int on);

void spiStartTransaction(void);

void spiStopTransaction(void);

static uint8_t rxbuf[32];
static uint8_t txbuf[32];
static SEMAPHORE_DECL(sem, 0);

void WriteRegister(int  numRegistre, int numMots, uint8_t* wtxbuf);

void WriteRegisterByte(int numRegister, uint8_t value);

void ReadRegister(int numRegister, int numBytes, uint8_t* rrxbuf );

uint8_t ReadRegisterByte(int numRegister);

void ExecuteCommand(int command);

//To send data to an other radio, puts the data int the TX_PAYLOAD
void SendData(const uint8_t* datasend, int numWords);

void ReceivePacket(uint8_t *rxbuf, size_t pkt_size);

void ConfigureRF(int sizepck);

void switchOn(void);

void switchOff(void);

void SendMessage(uint8_t* txbuf);

void ReceiveMessage(void);

void irq_handler(EXTDriver *e, expchannel_t c);

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
	{EXT_CH_MODE_FALLING_EDGE | EXT_MODE_GPIOG | EXT_CH_MODE_AUTOSTART, irq_handler},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL},
	{EXT_CH_MODE_DISABLED,NULL}
  },
};
