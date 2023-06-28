#include "hm11.h"
#include "../MPU6050/mpu6050.h"

void Hm11_Init(void){
    /* ---------- UART Initialize ---------- */
    /* Initialize CoreUARTapb with its base address, baud value, and line configuration */
    UART_init( &g_uart_0, COREUARTAPB0_BASE_ADDR,
    		BAUD_VALUE_9600, (DATA_8_BITS | NO_PARITY) );
	NVIC_EnableIRQ(FabricIrq1_IRQn);
    
    

	calloc((uint8_t)_tx_buffer_, 15);
	calloc((uint8_t)_rx_buffer_, 32);
    return;
}

void Hm11_Packet(void){
    MPU6050_Read_Sens(&Mpu6050_);
    _tx_buffer_[0]  = Mpu6050_.Accel_X_RAW >> 8;
    _tx_buffer_[1]  = Mpu6050_.Accel_X_RAW;
    _tx_buffer_[2]  = Mpu6050_.Accel_Y_RAW >> 8;
    _tx_buffer_[3]  = Mpu6050_.Accel_Y_RAW;
    _tx_buffer_[4]  = Mpu6050_.Accel_Z_RAW >> 8;
    _tx_buffer_[5]  = Mpu6050_.Accel_Z_RAW;
    _tx_buffer_[6]  = Mpu6050_.Gyro_X_RAW >> 8;
    _tx_buffer_[7]  = Mpu6050_.Gyro_X_RAW;
    _tx_buffer_[8]  = Mpu6050_.Gyro_Y_RAW >> 8;
    _tx_buffer_[9]  = Mpu6050_.Gyro_Y_RAW;
    _tx_buffer_[10] = Mpu6050_.Gyro_Z_RAW >> 8;
    _tx_buffer_[11] = Mpu6050_.Gyro_Z_RAW;
    _tx_buffer_[12] = Mpu6050_.Temp_RAW >> 8;
    _tx_buffer_[13] = Mpu6050_.Temp_RAW;
    _tx_buffer_[14] = Mpu6050_.Sensitivity;
}

void FabricIrq1_IRQHandler(void){
    volatile uint8_t rx_size = 0;
    rx_size = UART_get_rx(&g_uart_0, _rx_buffer_, sizeof(_rx_buffer_));
	return;
}
void HardFault_Handler(void){

}

