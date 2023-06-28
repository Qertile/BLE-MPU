#include "hm11.h"
#include "../MPU6050/mpu6050.h"

void Hm11_Init(void){
    /* ---------- UART Initialize ---------- */
    /* Initialize CoreUARTapb with its base address, baud value, and line configuration */
    UART_init( &g_uart_0, COREUARTAPB0_BASE_ADDR,
    		BAUD_VALUE_115200, (DATA_8_BITS | NO_PARITY) );
	NVIC_EnableIRQ(FabricIrq1_IRQn);

	_tx_buffer_ = (uint8_t*)calloc(0, UART_TX_BUFF_SIZE);
	_rx_buffer_ = (uint8_t*)calloc(0, UART_RX_BUFF_SIZE);
    return;
}

void Hm11_Packet(void){
    uint8_t crc8 = 0;
    for (uint8_t i=0; i<5; i++){
    	MPU6050_Read_All(&Mpu6050_);
        MPU6050_Read_Sens(&Mpu6050_);
        _tx_buffer_[20*i]    = HEADER_1;
        _tx_buffer_[20*i+1]  = HEADER_2;
        _tx_buffer_[20*i+2]  = Mpu6050_.Accel_X_RAW >> 8;
        _tx_buffer_[20*i+3]  = Mpu6050_.Accel_X_RAW;
        _tx_buffer_[20*i+4]  = Mpu6050_.Accel_Y_RAW >> 8;
        _tx_buffer_[20*i+5]  = Mpu6050_.Accel_Y_RAW;
        _tx_buffer_[20*i+6]  = Mpu6050_.Accel_Z_RAW >> 8;
        _tx_buffer_[20*i+7]  = Mpu6050_.Accel_Z_RAW;
        _tx_buffer_[20*i+8]  = Mpu6050_.Gyro_X_RAW >> 8;
        _tx_buffer_[20*i+9]  = Mpu6050_.Gyro_X_RAW;
        _tx_buffer_[20*i+10] = Mpu6050_.Gyro_Y_RAW >> 8;
        _tx_buffer_[20*i+11] = Mpu6050_.Gyro_Y_RAW;
        _tx_buffer_[20*i+12] = Mpu6050_.Gyro_Z_RAW >> 8;
        _tx_buffer_[20*i+13] = Mpu6050_.Gyro_Z_RAW;
        _tx_buffer_[20*i+14] = Mpu6050_.Temp_RAW >> 8;
        _tx_buffer_[20*i+15] = Mpu6050_.Temp_RAW;
        _tx_buffer_[20*i+16] = Mpu6050_.Sensitivity;
        _tx_buffer_[20*i+17] = 0x00;
        _tx_buffer_[20*i+18] = 0x00;
        _tx_buffer_[20*i+19] = Crc8(_tx_buffer_+(20*i), 19);;
    }

}

void FabricIrq1_IRQHandler(void){
    volatile uint8_t rx_size = 0;
    rx_size = UART_get_rx(&g_uart_0, _rx_buffer_, UART_RX_BUFF_SIZE);
	return;
}
void HardFault_Handler(void){

}

