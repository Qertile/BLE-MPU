/**
  ******************************************************************************
  * @file           : mpu6050.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * Author: Anastasis Vagenas -> Contact: anasvag29@gmail.com
  * Editor: YuShun Wang       -> Contact: wys601549@g.ncu.edu.tw
  *
  ******************************************************************************
  **/
#ifndef MPU6050_H_
#define MPU6050_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../../firmware/CMSIS/m2sxxx.h"
#include "../../firmware/drivers/CoreI2C/core_i2c.h"
#include "../../firmware/drivers_config/sys_config/sys_config.h"

#define MPU6050_SELF_TEST
#define DEBUG_MPU6050


/* ----- I2C Related ----- */
#define COREI2C_BASE_ADDR   0x50000000
#define COREI2C_SER_ADDR    0xFF
#define I2C_TIMEOUT         10        // ms

/* ----- MPU6050 Related ----- */
#define MPU6050_ADDR_LOW    0x68    // 7-Bit address when AD0 is connect to GND //
#define MPU6050_ADDR_HIGH   0x69    // 7-Bit address when AD0 is connect to VCC //
// #define MPU6050_WRITE_ADDR 	0xD0    // 8-Bit Write address //
// #define MPU6050_READ_ADDR 	0xD1    // 8-Bit Read address //
 #define MPU6050_DEVICE_ID 	0x68

/* ----- MPU6050 Return codes ----- */
#define MPU6050_SUCCESS   0
#define MPU6050_FAILURE   1

/* ----- Gyro sensitivities in g/s ----- */
#define GYRO_SENS_250_DEG	  ((float) 131.0)
#define GYRO_SENS_500_DEG	  ((float) 65.5)
#define GYRO_SENS_1K_DEG	  ((float) 32.8)
#define GYRO_SENS_2K_DEG	  ((float) 16.4)

/* ----- Gyro register value for sensitivity ----- */
#define GYRO_SCALE_250_DEG    0x00
#define GYRO_SCALE_500_DEG    0x08
#define GYRO_SCALE_1K_DEG     0x10
#define GYRO_SCALE_2K_DEG     0x18

/* ----- Accel sensitivities in g/s ----- */
#define ACCEL_SENS_2G       ((float) 16384.0)
#define ACCEL_SENS_4G       ((float) 8192.0)
#define ACCEL_SENS_8G       ((float) 4096.0)
#define ACCEL_SENS_16G	    ((float) 2048.0)

/* ----- Accel register value for sensitivity ----- */
#define ACCEL_SCALE_2G    0x00
#define ACCEL_SCALE_4G    0x08
#define ACCEL_SCALE_8G    0x10
#define ACCEL_SCALE_16G   0x18

/* ----- Power Managlement Reg 1 Parameters ----- */
#define PWR_WAKE_UP       0x00
#define ENABLE_SLEEP      0x40
#define ENABLE_CYCLE      0x20
#define TEMP_DIS          0x08    // Disable temperature sensor //

/* ----- Power Managlement Reg 2 Parameters ----- */
#define GYRO_STBY         0x07    // Standby for every axis //
#define ACCEL_STBY        0x38    // Standby for every axis //

// Cycle Mode Wake-Up Frequency //
#define LP_WAKE_FREQ_1_25HZ  0x00
#define LP_WAKE_FREQ_5HZ     0x40
#define LP_WAKE_FREQ_20HZ    0x80
#define LP_WAKE_FREQ_40HZ    0xc0

// Kalman calculation constants //
#define RAD_TO_DEG 57.295779513082320876798154814105

// Self_test //
#define ACCEL_ENABLE_SELF_TEST    0xe0
#define GYRO_ENABLE_SELF_TEST     0xe0
// Self_test parameters //
#define GYRO_SELF_TEST_MASK 		    0x1f
#define GYRO_CONSTANT_MULT 		      3275
#define GYRO_CONSTANT_BASE 		      1.046
#define ACCEL_SELF_TEST_UPPER_MASK 	0xE0
#define ACCEL_SELF_TEST_X_MASK 		  0x30
#define ACCEL_SELF_TEST_X_SHIFT 	    4
#define ACCEL_SELF_TEST_Y_MASK 		  0x0c
#define ACCEL_SELF_TEST_Y_SHIFT 	    2
#define ACCEL_SELF_TEST_Z_MASK 		  0x03
#define ACCEL_SELF_TEST_Z_SHIFT 	    0
#define ACCEL_CONSTANT_MULT 		    1392.64
#define ACCEL_CONSTANT_BASE 		    2.7058
#define MAX_SELF_TEST_VAL 		      14.0

/* ========== Enums ========== */
/* Enum that has the register addresses of the MPU6050 registers.
 * Contains registers that are also not used in case of expanding the driver.
 *
 * Not all registers are needed due to the fact that MPU6050 supports
 * burst read (read multiple bytes continuously, like the ACCEL_X_OUT).
 *
 * So for example if you want to read the ACCEL values, you read from the
 * first register that stores them and read the next 5 registers
 * (The ACCEL values are stored continuously in memory).
 */
typedef enum mpu6050_register_address
{
  PWR_MGMT_1_REG = 0x6B,
  PWR_MGMT_2_REG = 0x6C,
  SMPLRT_DIV_REG = 0x19,
  ACCEL_CONFIG_REG = 0x1C,
  ACCEL_XOUT_H_REG = 0x3B,
  SELF_TEST_REG = 0x0D,
  TEMP_OUT_H_REG = 0x41,
  GYRO_CONFIG_REG = 0x1B,
  GYRO_XOUT_H_REG = 0x43,
  INT_PIN_CFG_REG = 0x37,
  INT_ENABLE_REG = 0x38,
  INT_STATUS_REG = 0x3A,
  WHO_AM_I_REG = 0x75
}mpu6050_reg_add;

/* Enum that has the MPU6050 sample rate for each part of it
 * @Note: If you read values faster than the sample rate you will read
 * the same value
 */
typedef enum
{
  MPU6050_DataRate_8KHz = 0x00,     // Sample rate set to 8 kHz  //
  MPU6050_DataRate_4KHz = 0x01,     // Sample rate set to 4 kHz  //
  MPU6050_DataRate_2KHz = 0x03,     // Sample rate set to 2 kHz  //
  MPU6050_DataRate_1KHz = 0x07,     // Sample rate set to 1 kHz  //
  MPU6050_DataRate_500Hz = 0x0F,    // Sample rate set to 500 Hz //
  MPU6050_DataRate_250Hz = 0x1F,    // Sample rate set to 250 Hz //
  MPU6050_DataRate_125Hz = 0x3F,    // Sample rate set to 125 Hz //
  MPU6050_DataRate_100Hz = 0x4F,    // Sample rate set to 100 Hz //
} MPU6050_sample_rate_conf;

/* Enum that has the accelerometer sensitivity values
 * These values have to be written to the accel config register
 * in order to change the sensitivity.
 */
typedef enum
{
  MPU6050_Accelerometer_2G = 0x00,  // Range is +- 2G  //
  MPU6050_Accelerometer_4G = 0x01,  // Range is +- 4G  //
  MPU6050_Accelerometer_8G = 0x02,  // Range is +- 8G  //
  MPU6050_Accelerometer_16G = 0x03  // Range is +- 16G //
} MPU6050_Accelerometer_conf;

/* Enum that has the gyro sensitivity values
 * These values have to be written to the gyro config register
 * in order to change the sensitivity.
 */
typedef enum
{
  MPU6050_Gyroscope_250_deg = 0x00,  // Range is +- 250 degrees/s  //
  MPU6050_Gyroscope_500_deg = 0x01,  // Range is +- 500 degrees/s  //
  MPU6050_Gyroscope_1000_deg = 0x02, // Range is +- 1000 degrees/s //
  MPU6050_Gyroscope_2000_deg = 0x03  // Range is +- 2000 degrees/s //
} MPU6050_Gyroscope_conf;

/* Enum that has the MPU6050 power profile
 * Depending on the user choice the MPU6050 sets the registers
 * POWER_MANAGEMENT 1/2 .
 */
typedef enum
{
  MPU6050_ACCEL_ONLY = 0x00,    // Accelerometer only mode             //
  MPU6050_GYRO_ONLY,            // Gyroscope only mode                 //
  MPU6050_CYCLE,                // Cycle Mode - Sample at a fixed rate //
  MPU6050_SLEEP,                // Sleep mode - Everything Disabled    //
  MPU6050_POWER_ON,             // Power ON - Everything ON            //
} MPU6050_power_conf;

/* Enum that has the MPU6050 sample rate when configured for low power mode
 * Depending on the user choice the MPU6050 sets the registers
 * POWER_MANAGEMENT 1 and 2 .
 */
typedef enum
{
  MPU6050_low_power_1_25Hz = 0x00,   // Sample Rate 1.25Hz               //
  MPU6050_low_power_5Hz,             // Sample Rate 5Hz                  //
  MPU6050_low_power_20Hz,            // Sample Rate 20Hz                 //
  MPU6050_low_power_40Hz,            // Sample Rate 40Hz                 //
  MPU6050_rate_dont_care,            // We don't care about sample rate  //
} MPU6050_low_power_sample_conf;

/* ========== Data Structures ========== */
/* MPU6050 structure that contains the measurements from MPU6050
 * It contains the raw ADC Values and the float values from each of the following:
 * - Temperature (Raw and decimal)
 * - Accelerometer (Raw and decimal)
 * - Gyroscope (Raw and decimal)
 * - Angle (Pitch and Roll)
 */
typedef struct {
  /* Acceleration */  
  int16_t Accel_X_RAW;
  int16_t Accel_Y_RAW;
  int16_t Accel_Z_RAW;
  double Ax;
  double Ay;
  double Az;

  /* Gyro Acceleration */
  int16_t Gyro_X_RAW;
  int16_t Gyro_Y_RAW;
  int16_t Gyro_Z_RAW;
  double Gx;
  double Gy;
  double Gz;

  /* Temperature */
  int16_t Temp_RAW;
  float   Temperature;
  
  /* Configuration */
  uint8_t Sensitivity;

  /* Angle -> Pitch/Roll */
  double KalmanAngleX;
  double KalmanAngleY;

} MPU6050_t;

/* Kalman structure that is used to calculate the Kalman angle,
 * basically pitch and roll.
 */
typedef struct {
  double Q_angle;
  double Q_bias;
  double R_measure;
  double angle;
  double bias;
  double P[2][2];

} Kalman_t;

/* MPU6050_configuration structure
 * Contains the active configuration and status of the MPU6050.
 */
typedef struct MPU6050_configuration{
  float gyro_sensitivity;
  float accel_sensitivity;
  uint8_t power_mode;
  uint8_t freq;
  uint8_t irq_enable;
} Mpu6050_Config_t;


/* ========== Global Variables ========== */
Mpu6050_Config_t Mpu6050_Config_;
MPU6050_t Mpu6050_;
/* ----- coreI2C instance ----- */
 i2c_instance_t g_core_i2c0;

/* ========== Functions ========== */
/** ------------------ Mpu_Init() ------------------
 *  @brief
 *      This function will initialize the coreI2C and MPU6050
 *
 *  @param 
 *      This function doesn't require any input
 *
 *  @return
 *      This function returns nothing
 **/
void Mpu_Init(void);

/* Functions -----------------------------------------------------------------*/
uint8_t MPU6050_Init(uint8_t accel_config, uint8_t gyro_config, uint8_t sample_rate);
void MPU6050_set_power_mode(uint8_t power_mode, uint8_t freq);
// void MPU6050_enable_irq(uint8_t config);
// void MPU6050_disable_irq(void);
// uint8_t MPU6050_get_irq_status(void);
// void MPU6050_peripheral_config(void);
void MPU6050_Read_Sens(MPU6050_t *DataStruct);
void MPU6050_Read_Accel(MPU6050_t *DataStruct);
void MPU6050_Read_Gyro(MPU6050_t *DataStruct);
void MPU6050_Read_Temp(MPU6050_t *DataStruct);
void MPU6050_Read_All(MPU6050_t *DataStruct);
double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt);

static void I2C_Initalize(void);

extern void I2C_enable_irq( i2c_instance_t * this_i2c );

#endif
