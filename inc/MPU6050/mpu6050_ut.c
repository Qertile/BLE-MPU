//#include "mpu6050.h"
//
//
// int main(void){
//
//	// Main Data structure //
//	MPU6050_t MPU6050;
//
////	MPU6050_peripheral_config();
//	uint8_t check = MPU6050_Init(MPU6050_Accelerometer_2G, MPU6050_Gyroscope_250_deg, MPU6050_DataRate_1KHz);
//
//	// Check if INIT was successful //
//	if(check == MPU6050_SUCCESS)
//		printf("MPU6050 Initialization Success\n");
//
//	// Set power mode //
//	MPU6050_set_power_mode(MPU6050_POWER_ON, MPU6050_rate_dont_care);
//	while (1){
//		MPU6050_Read_All(&MPU6050);
//	}
//
// 	return 0;
// }
