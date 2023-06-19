# BT-Gyro
A project that using SmartFusion2 to control a gyroscope MPU6050 on the GY521 module and connect to PC by a bluetooth module HM11. This repository contains the drivers of MUP6050 and HM11

-----------------------------------
## Unreleased v0.0.3(2023.06.##) @master
### New
### Changed
1. rename `MPU6050_config_t mpu6050_config `related usage to `Mpu6050_Config_t Mpu6050_Config_`
2. comment out unuse STM32 related functions
3. rename all `i2c_MPU6050_write_reg` and `i2c_MPU6050_read_reg` `i2c_MPU6050_write` to `i2c_MPU6050_read` in .c file
### Removed
### Deprecated
### Fixed
1. fix all errors while building project
### Known Issues
### Notes
### Reference
-----------------------------------
## BT-Gyro v0.1.0(2023.06.19) @master
### Changed
1. rename `MPU6050_config_t mpu6050_config `related usage to `Mpu6050_Config_t Mpu6050_Config_`
2. comment out unuse STM32 related functions
3. rename all `i2c_MPU6050_write_reg` and `i2c_MPU6050_read_reg` `i2c_MPU6050_write` to `i2c_MPU6050_read` in .c file
### Fixed
1. fix all errors while building project

-----------------------------------
## BT-Gyro v0.0.2(2023.06.19) @master
### New
1. create corei2c_driver.h
### Changed
1. modify i2c_MPU6050_write_reg for SF2
2. modify i2c_MPU6050_read_reg for SF2

-----------------------------------
## BT-Gyro v0.0.1(2023.06.16) @master
### New
1. create `Mpu6050_Init()`
2. import mpu6050.h from [MPU6050_driver](https://github.com/anasvag575/MPU6050_driver.git)
3. import mpu6050.c from [MPU6050_driver](https://github.com/anasvag575/MPU6050_driver.git)
### Reference
1. [MPU6050_driver](https://github.com/anasvag575/MPU6050_driver.git)
