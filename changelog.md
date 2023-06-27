# BT-Gyro
A project that using SmartFusion2 to control a gyroscope MPU6050 on the GY521 module and connect to PC by a bluetooth module HM11. This repository contains the drivers of MUP6050 and HM11

-----------------------------------
## To-Do
- [ ] switch temperature data to raw
- [ ] packet sensitivity configuration

-----------------------------------
## Unreleased v0.3.1(2023.06.##) @master
### New
1. create `Temp_RAW` in MPU6050_t
2. store temperature raw value MPU6050_t
### Changed
### Removed
### Deprecated
### Fixed
### Known Issues
### Notes
### Reference

-----------------------------------
## BT-Gyro v0.3.1(2023.06.26) @master
### New
- integrate MPU6050 and HM11
- test with MPU6050 and HM11
-----------------------------------
## BT-Gyro v0.3.0(2023.06.26) @master
### New
- create Hm11_Init()

-----------------------------------
## BT-Gyro v0.2.1(2023.06.26) @master
### New
- create HM11.h, HM11.c, and HM11_ut.c
  
-----------------------------------
## BT-Gyro v0.2.0(2023.06.26) @master
### New
- create a new function `I2C_init()`
### Changed
- refactor `MPU6050_Read_All()`
### Removed
- remove memset in `i2c_MPU6050_read()`
### Fixed
- I2C will freeze if too much transaction in a specific period of time (re-initial if I2C timeout)
### Known Issues
- I2C will freeze if too much transaction in a specific period of time
### Notes
- currently not use kalman angle functions, since it needs systick as timer
  
-----------------------------------
## BT-Gyro v0.1.3(2023.06.26) @master
### New
1. receive data into rx buffer 
2. set timeout for `i2c_wait_complete()`
### Notes
1. write_read is basiclly == write + read

-----------------------------------
## BT-Gyro v0.1.2(2023.06.21) @master
### Fixed
1. fix device didn’t response to commands (issue #3)

-----------------------------------
## BT-Gyro v0.1.1(2023.06.20) @master
### New
1. include "m2sxxx.h" in "i2c_interrupt.c"
### Changed
1. rename `g_i2C_inst_0` to `g_core_i2c0`
### Fixed
1. fix code jumps into `I2C_enable_irq()` (issue #1)
2. fix no signal while using `I2C_write()` (issue #2)

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
