#include "hm11.h"

static void Hm11_Init(void){
    /* ---------- UART Initialize ---------- */
    /* Initialize CoreUARTapb with its base address, baud value, and line configuration */
    UART_init( &g_uart_0, COREUARTAPB0_BASE_ADDR,
               BAUD_VALUE_115200, (DATA_8_BITS | NO_PARITY) );
	NVIC_EnableIRQ(FabricIrq1_IRQn);
    return;
}

void FabricIrq1_IRQHandler(void){
    volatile uint8_t rx_size = 0;
    rx_size = UART_get_rx(&g_uart_0, _rx_buffer_, sizeof(_rx_buffer_));
	return;
}

