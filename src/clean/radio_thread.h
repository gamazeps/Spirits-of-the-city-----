#ifndef RADIO_THREAD_H
#define RADIO_THREAD_H

#include "ch.h"
#include "hal.h"

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

// Buffers d'émission et réception
extern uint8_t rxbuf[SIZEPKT];
extern uint8_t txbuf[SIZEPKT];

void radio_init(void);
void send_message(uint8_t* ttxbuf);
int receive_animation(void);
void await_animation(void);

#endif

