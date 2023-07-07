#include "hm11.h"
#include "../MPU6050/mpu6050.h"

	// uint32_t j;
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
    MPU6050_Read_All(&Mpu6050_);
    MPU6050_Read_Sens(&Mpu6050_);
    _tx_buffer_[0]  = HEADER_1;
    _tx_buffer_[1]  = HEADER_2;
    _tx_buffer_[2]  = Mpu6050_.Accel_X_RAW >> 8;
    _tx_buffer_[3]  = Mpu6050_.Accel_X_RAW;
    _tx_buffer_[4]  = Mpu6050_.Accel_Y_RAW >> 8;
    _tx_buffer_[5]  = Mpu6050_.Accel_Y_RAW;
    _tx_buffer_[6]  = Mpu6050_.Accel_Z_RAW >> 8;
    _tx_buffer_[7]  = Mpu6050_.Accel_Z_RAW;
    _tx_buffer_[8]  = Mpu6050_.Gyro_X_RAW >> 8;
    _tx_buffer_[9]  = Mpu6050_.Gyro_X_RAW;
    _tx_buffer_[10] = Mpu6050_.Gyro_Y_RAW >> 8;
    _tx_buffer_[11] = Mpu6050_.Gyro_Y_RAW;
    _tx_buffer_[12] = Mpu6050_.Gyro_Z_RAW >> 8;
    _tx_buffer_[13] = Mpu6050_.Gyro_Z_RAW;
    _tx_buffer_[14] = Mpu6050_.Temp_RAW >> 8;
    _tx_buffer_[15] = Mpu6050_.Temp_RAW;
    _tx_buffer_[16] = Mpu6050_.Sensitivity;
    _tx_buffer_[17] = 0x00;
    _tx_buffer_[18] = 0x00;
    _tx_buffer_[19] = Crc8(_tx_buffer_, 19);;



	// for(uint8_t i=0; i<20; i++) {
	// 	_tx_buffer_[i] = j;
	// 	j++;
	// }
//	_tx_buffer_[19] = 0x0A;

    /* minimum delay before UART transmission */
//	for(int i=0; i<250; i++){for(int j=0; j<250; j++){;}}
}

void FabricIrq1_IRQHandler(void){
    volatile uint8_t rx_size = 0;
    rx_size = UART_get_rx(&g_uart_0, _rx_buffer_, UART_RX_BUFF_SIZE);
	return;
}
void HardFault_Handler(void){

}

void SysTick_Handler(void) {
    static uint32_t count = 0;
    static uint16_t num_packet = 0;

    I2C_system_tick(&g_core_i2c0, 1);
    if(_tx_buffer_ != ( int8_t* ) 0){
        if (count == 10){
            // UART tx every 10 ticks (10ms)
    		Hm11_Packet();
            UART_send( &g_uart_0, _tx_buffer_, 20 );
            num_packet++;
            count = 0;
        }
    }
    count++;
}

