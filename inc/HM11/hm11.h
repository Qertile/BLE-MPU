#ifndef HM11_H_
#define HM11_H_

#include <stdint.h>
#include <string.h>
#include "../../firmware/drivers/CoreUARTapb/core_uart_apb.h"
#include "../../firmware/CMSIS/m2sxxx.h"

/* ----- UART Parameters ----- */
#define COREUARTAPB0_BASE_ADDR   0x50001000
#define BAUD_VALUE_115200    53 // 53.25
#define APRS_BUFF_SIZE    256

/* ----- CoreUARTapb instance ----- */
UART_instance_t g_uart_0;


/* ----- Global variables ----- */
uint8_t _rx_buffer_[32];


/* ----- Functions ----- */
static void Hm11_Init(void);
extern void FabricIrq1_IRQHandler(void);



#endif
