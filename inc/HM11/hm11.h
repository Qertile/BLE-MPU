#ifndef HM11_H_
#define HM11_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../../firmware/drivers/CoreUARTapb/core_uart_apb.h"
#include "../../firmware/CMSIS/m2sxxx.h"
#include "../CRC8/crc8.h"

/* ----- UART Parameters ----- */
#define COREUARTAPB0_BASE_ADDR   0x50001000
#define BAUD_VALUE_115200    53 // 53.25
#define BAUD_VALUE_230400	 26 // 26.12
#define BAUD_VALUE_38400     162 // 161.76
#define BAUD_VALUE_9600      650 // 650.04
#define APRS_BUFF_SIZE       256

#define UART_TX_BUFF_SIZE 20
#define UART_RX_BUFF_SIZE 32

/* ----- Packet Parameters ----- */
#define HEADER_1    0x41
#define HEADER_2    0x58

/* ----- CoreUARTapb instance ----- */
UART_instance_t g_uart_0;


/* ----- Global variables ----- */
uint8_t *_rx_buffer_;
int8_t *_tx_buffer_;

/* ----- Functions ----- */
void Hm11_Packet(void);
void Hm11_Init(void);
extern void FabricIrq1_IRQHandler(void);



#endif
