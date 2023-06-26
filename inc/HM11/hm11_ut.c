#include "hm11.h"

int main(void){
    /* ---------- UART Initialize ---------- */
    /* Initialize CoreUARTapb with its base address, baud value, and line configuration */
    UART_init( &g_uart_0, COREUARTAPB0_BASE_ADDR,
               BAUD_VALUE_115200, (DATA_8_BITS | NO_PARITY) );
	NVIC_EnableIRQ(FabricIrq1_IRQn);


    /* ---------- UART Transaction ---------- */
    uint8_t rx_size = 0;
//    UART_send( &g_uart_0, _tx_buffer_, sizeof(_tx_buffer_) );

    rx_size = UART_get_rx( &g_uart_0, _rx_buffer_, sizeof(_rx_buffer_) );

    while(1);
	return 0;
}
