#include "./mpu6050.h"


void Mpu6050_Init(void){
    // MPU6050 fast mode is 400kHz std mode is 100 kHz
    I2C_init( g_i2c_inst_0, COREI2C_BASE_ADDR, COREI2C_SER_ADDR, I2C_PCLK_DIV_256);

}