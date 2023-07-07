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

    Hm11_.Frequency = 0x00;
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
    _tx_buffer_[17] = Mpu6050_.Num_packet >> 8;
    _tx_buffer_[18] = Mpu6050_.Num_packet;

    _tx_buffer_[16] = _tx_buffer_[16] | (Hm11_.Frequency<<6) ;

    _tx_buffer_[19] = Crc8(_tx_buffer_, 19);


}

void FabricIrq1_IRQHandler(void){
    volatile uint8_t rx_size = 0;
    rx_size = UART_get_rx(&g_uart_0, _rx_buffer_, UART_RX_BUFF_SIZE);

    if (_rx_buffer_[0] == 0x41 && _rx_buffer_[1] == 0x58){
        switch (_rx_buffer_[2]){
        case HM11_RESET:
            break;
        case HM11_TX_ON:
            Hm11_.Onoff = HM11_TX_ON;
            break;
        case HM11_TX_OFF:
            Hm11_.Onoff = HM11_TX_OFF;
            break;
        case HM11_SET_TX_FREQ:
            Hm11_.Frequency = _rx_buffer_[3];
            break;
        
        default:
            break;
        }
    }
	return;
}
void HardFault_Handler(void){

}

void SysTick_Handler(void) {
    static uint32_t count = 0;
    volatile tx_rate = 0;   // number of ticks to transmit packet, 1 tick is 1 ms

    I2C_system_tick(&g_core_i2c0, 1);

    switch(Hm11_.Frequency){
        case HM11_TX_RATE_100:
            tx_rate = 10;
            break;
        case HM11_TX_RATE_10:
            tx_rate = 100;
        case HM11_TX_RATE_1:
            tx_rate = 1000;
            break;
        default:
            tx_rate = 10;
            break
    }

    if(_tx_buffer_ != ( int8_t* ) 0){
        if (count == tx_rate){
            switch(Hm11_.Onoff){
                case HM11_TX_ON:
                    // UART tx every 10 ticks (10ms)
                    Hm11_Packet();
                    UART_send( &g_uart_0, _tx_buffer_, UART_TX_BUFF_SIZE );
                    Mpu6050_.Num_packet++;
                    break;
                case HM11_TX_OFF:
                    break;
            }

            count = 0;
        }
    }
    count++;
}

