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
	memset(&Hm11_, 0, sizeof(HM11_t));

    Hm11_.onoff = 0x00;
    Hm11_.frequency = 0x00;
    Hm11_.tx_tick = 10;
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
    _tx_buffer_[17] = Hm11_.Num_packet >> 8;
    _tx_buffer_[18] = Hm11_.Num_packet;

    _tx_buffer_[16] = _tx_buffer_[16] | (Hm11_.frequency<<6) ;

    _tx_buffer_[19] = Crc8(_tx_buffer_, 19);

    return;
}

void Hm11_Is_Rx_Full(void){
    if(_rx_buffer_[7]!=0) {
        for (uint8_t i=0; i<UART_RX_BUFF_SIZE; i++)
            Hm11_.last_cmd[i] = _rx_buffer_[i];

        memset(_rx_buffer_, 0, UART_RX_BUFF_SIZE);
        UART_send( &g_uart_0, Hm11_.last_cmd, UART_RX_BUFF_SIZE );
    }
    return;
}

void Hm11_Config_By_Cmd(void){
    if (Hm11_.last_cmd[0] == 0x41 && Hm11_.last_cmd[1] == 0x58){
        switch (Hm11_.last_cmd[2]){
            case HM11_RESET:
                break;
            case HM11_TX_ON:
                Hm11_.onoff = HM11_TX_ON;
                break;
            case HM11_TX_OFF:
                Hm11_.onoff = HM11_TX_OFF;
                Hm11_.Num_packet = 0;
                break;
            case HM11_SET_TX_FREQ:
                Hm11_.frequency = Hm11_.last_cmd[3];
                break;
            default:
                break;
        }
        switch(Hm11_.frequency){
            case HM11_TX_RATE_100:
                Hm11_.tx_tick = 10;
                break;
            case HM11_TX_RATE_10:
                Hm11_.tx_tick = 100;
                break;
            case HM11_TX_RATE_1:
                Hm11_.tx_tick = 1000;
                break;
            default:
                Hm11_.tx_tick = 10;
                break;
        }   
        memset(Hm11_.last_cmd, 0, UART_RX_BUFF_SIZE);
    }
}

void FabricIrq1_IRQHandler(void){
    uint8_t rx_size = 0;
    uint8_t static idx = 0;
    
    rx_size = UART_get_rx(&g_uart_0, _rx_buffer_ + idx, UART_RX_BUFF_SIZE);
    idx += rx_size;
    if (idx == UART_RX_BUFF_SIZE) idx = 0;
	return;
}

void SysTick_Handler(void) {
    static uint32_t count = 0;
    static uint16_t last_tx_rate = 0; // to detect the change of tx_rate

    I2C_system_tick(&g_core_i2c0, 1);
    last_tx_rate = Hm11_.tx_tick;

    Hm11_Config_By_Cmd();

    if(Hm11_.tx_tick != last_tx_rate) count = 0; // tx rate is changed, reset counter
    if(_tx_buffer_ != ( int8_t* ) 0){
        if (count == Hm11_.tx_tick){
            switch(Hm11_.onoff){
                case HM11_TX_ON:
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

