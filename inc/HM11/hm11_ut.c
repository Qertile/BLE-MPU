#include "hm11.h"

int main(void){
    /* ---------- UART Transaction ---------- */
    uint8_t rx_size = 0;
//    UART_send( &g_uart_0, _tx_buffer_, sizeof(_tx_buffer_) );

    rx_size = UART_get_rx( &g_uart_0, _rx_buffer_, sizeof(_rx_buffer_) );

    while(1);
	return 0;
}
