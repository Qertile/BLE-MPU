# BT-Gyro
A project that using SmartFusion2 to control a gyroscope MPU6050 on the GY521 module and connect to PC by a bluetooth module HM11. This repository contains the drivers of MUP6050 and HM11

-----------------------------------
## To-Do
- [ ] add time in packet
- [ ] command receive handler

-----------------------------------
## Unreleased v1.#.#(2023.07.##) @master
### New
- create `num_packet` in `SysTick_Handler()`
### Changed
### Removed
### Deprecated
### Fixed
### Known Issues
### Notes
### Reference

-----------------------------------
## BT-Gyro v1.0.0(2023.07.05) @master
### New
- release v0.7.0


-----------------------------------
## BT-Gyro v0.7.0(2023.07.05) @master
### Changed
- set systick to 1 ms to match the minimum value of I2C_system_tick()
### Fixed
- I2C is alive but data is always 0 (Issue #7)
 

-----------------------------------
## BT-Gyro v0.6.2(2023.07.04) @master
### Changed
1. move `Hm11_Packet()` into `SysTick_Handler()`
2. set count in `SysTick_Handler()` to 5000 let UART transmit every 10 ms
### Known Issues
1. I2C is alive but data is always 0 (Issue #7)


-----------------------------------
## BT-Gyro v0.6.1(2023.07.04) @master
### New
1. config systick as a 2 us tick
2. control UART tx interval by `count` in `SysTick_Handler()`
### Changed
1. modify timeout of `I2C_system_tick()` to 1 ms
2. modify `SysTick_Config()` to 1 us tick
3. move `SysTick_Handler()` from mpu6050.c to hm11.c
4. move `UART_send()` into `SysTick_Handler()`

-----------------------------------
## BT-Gyro v0.6.0(2023.07.04) @master
### New
1. add delay before next uart transmission
### Removed
1. remove packet 5 data as one 100-bytes packet

-----------------------------------
## BT-Gyro  v0.5.1(2023.07.04) @master
### Changed
1. test the relationship between packet size and the correctness of received data
### Notes
1. If BLE packet is not 10 or 20 bytes, data will be corrupted
2. In BLE 4.0 and 4.1, max ATT payload size is 20 bytes

-----------------------------------
## BT-Gyro v0.5.0(2023.06.28) @master
### New
1. add header "AX", pad 2 bytes zero, and CRC8 at the end of packet (to make packet 20 bytes length)
2. create packet HEADER `HEADER_1` and `HEADER_2`
3. create crc8 functions
### Notes
- uart 115200 is fine, 230400 will lead to hardfault
  
-----------------------------------
## BT-Gyro v0.4.1(2023.06.28) @master
### Changed
1. move SysTick_IRQn priority setting from `Hm11_Init()` to `MPU6050_Init()`
2. move systick config from `I2C_Initialize()` to `MPU6050_Init()`
3. maybe the priority of I2C irq is higher than UART irq
4. change HM11 baudrate to 
### Fixed
1. program go to hardfault handler if using while (1) to do UART and I2C tranction

-----------------------------------
## BT-Gyro v0.4.0(2023.06.27) @master
### New
- create `Sensitivity` in MPU6050_t
- create function `MPU6050_Read_Sens()`
### Fixed
1. temp is always zero
2. configuration always zero (zero is correct, need to modify packet definition)
### Known Issues
1. program go to hardfault handler if using while (1) to do UART and I2C tranction

-----------------------------------
## BT-Gyro v0.3.2(2023.06.27) @master
### New
1. create `Temp_RAW` in MPU6050_t
2. store raw temperature value MPU6050_t
3. update raw temperature data into packet

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
