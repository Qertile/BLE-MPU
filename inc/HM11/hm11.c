#include "hm11.h"



void FabricIrq1_IRQHandler(void){

    volatile uint8_t rx_size = 0;

    rx_size = UART_get_rx(&g_uart_0, _rx_buffer_, sizeof(_rx_buffer_));
	return;
}

