# BT-Gyro
A project that using SmartFusion2 to control a gyroscope MPU6050 on the GY521 module and connect to PC by a bluetooth module HM11. This repository contains the drivers of MUP6050 and HM11

-----------------------------------
## To-Do

-----------------------------------
## Unreleased v2.2.2 (2023.07.13) @master
### New
1. create AT+RESET and AT command in Hm11_init()
2. create `_at_RxBuff_` and `_at_TxBuff_`
### Changed
1. rename `_rx_buffer_` to `_ble_RxBuff_`
2. rename `_tx_buffer_` to `_ble_TxBuff_`
3. rename `UART_RX_BUFF_SIZE` to `BLE_RX_BUFF_SIZE`
3. rename `UART_TX_BUFF_SIZE` to `BLE_TX_BUFF_SIZE`
### Removed
### Deprecated
### Fixed
### Known Issues
### Notes
### Reference

-----------------------------------
## BT_Gyro v2.2.1 (2023.07.13) @master
### New
1. create and set default MODE0 in Hm11_init()
2. test and set default MODE0 in Hm11_init()
### Notes
1. User must disconnect BLE before using UART send any command


-----------------------------------
## BT-Gyro v2.2.0 (2023.07.11) @master
### New
1. test and release to SmartFusion2
### Changed
1. default Tx frequency is 1 Hz


-----------------------------------
## BT-Gyro v2.1.1 (2023.07.11) @master
### New
1. reset Num_packet when received Tx OFF command
### Changed
1. move `Num_packet` form `Mpu6050_` to `Hm11_`


-----------------------------------
## BT-Gyro v2.1.0 (2023.07.08) @master
### New
- release into SmartFusion2
### Known Issues
- software seems will reset itself some times

-----------------------------------
## BT-Gyro v2.0.1 (2023.07.08) @master
### Changed
- set default setting as onoff = 0, and tx_tick = 10


-----------------------------------
## BT-Gyro v2.0.0 (2023.07.07) @master
### New
1. Can receive command and modify tx frequency
2. Echo back command
3. release v2.0.0
### Fixed
1. BLE receive may not able to recive full command at one trancaction. 8 byte command will be received in 2 transactions -> 1 + 7
2. need to pause the program to receive commands


-----------------------------------
## BT-Gyro v1.1.0 (2023.07.07) @master
### New
1. create `last_tx_rate` in systick handler
2. reset `count` at the every change of `tx_rate`
### Fixed
1. fix errors while building v1.0.3
### Known Issues
1. BLE receive may not able to recive full command at one trancaction. 8 byte command will be received in 2 transactions -> 1 + 7
2. need to pause the program to receive commands


-----------------------------------
## BT-Gyro v1.0.3 (2023.07.07) @master
### New
1. create `tx_rate` in `SysTick_Handler()` 
2. create a switch to modify `tx_rate`
3. create a switch to control transmit on/off


-----------------------------------
## BT-Gyro v1.0.2 (2023.07.07) @master
### New
1. create `HM11_t`
2. create enum `HM11_COMMAND`
3. create a switch to handle received command
### Changed
1. change `UART_RX_BUFF_SIZE` to 8
2. change `UART_TX_BUFF_SIZE` to 20


-----------------------------------
## BT-Gyro v1.0.1 (2023.07.07) @master
### New
1. create `num_packet` in `SysTick_Handler()`
2. add `Num_packet` into packet
### Changed
1. move `num_packet` from `SysTick_Handler()` to `MPU6050_t`
2. comment other unused element in `MPU6050_t`


-----------------------------------
## BT-Gyro v1.0.0 (2023.07.05) @master
### New
- release v0.7.0


-----------------------------------
## BT-Gyro v0.7.0 (2023.07.05) @master
### Changed
- set systick to 1 ms to match the minimum value of I2C_system_tick()
### Fixed
- I2C is alive but data is always 0 (Issue #7)
 

-----------------------------------
## BT-Gyro v0.6.2 (2023.07.04) @master
### Changed
1. move `Hm11_Packet()` into `SysTick_Handler()`
2. set count in `SysTick_Handler()` to 5000 let UART transmit every 10 ms
### Known Issues
1. I2C is alive but data is always 0 (Issue #7)


-----------------------------------
## BT-Gyro v0.6.1 (2023.07.04) @master
### New
1. config systick as a 2 us tick
2. control UART tx interval by `count` in `SysTick_Handler()`
### Changed
1. modify timeout of `I2C_system_tick()` to 1 ms
2. modify `SysTick_Config()` to 1 us tick
3. move `SysTick_Handler()` from mpu6050.c to hm11.c
4. move `UART_send()` into `SysTick_Handler()`

-----------------------------------
## BT-Gyro v0.6.0 (2023.07.04) @master
### New
1. add delay before next uart transmission
### Removed
1. remove packet 5 data as one 100-bytes packet

-----------------------------------
## BT-Gyro  v0.5.1 (2023.07.04) @master
### Changed
1. test the relationship between packet size and the correctness of received data
### Notes
1. If BLE packet is not 10 or 20 bytes, data will be corrupted
2. In BLE 4.0 and 4.1, max ATT payload size is 20 bytes

-----------------------------------
## BT-Gyro v0.5.0 (2023.06.28) @master
### New
1. add header "AX", pad 2 bytes zero, and CRC8 at the end of packet (to make packet 20 bytes length)
2. create packet HEADER `HEADER_1` and `HEADER_2`
3. create crc8 functions
### Notes
- uart 115200 is fine, 230400 will lead to hardfault
  
-----------------------------------
## BT-Gyro v0.4.1 (2023.06.28) @master
### Changed
1. move SysTick_IRQn priority setting from `Hm11_Init()` to `MPU6050_Init()`
2. move systick config from `I2C_Initialize()` to `MPU6050_Init()`
3. maybe the priority of I2C irq is higher than UART irq
4. change HM11 baudrate to 
### Fixed
1. program go to hardfault handler if using while (1) to do UART and I2C tranction

-----------------------------------
## BT-Gyro v0.4.0 (2023.06.27) @master
### New
- create `Sensitivity` in MPU6050_t
- create function `MPU6050_Read_Sens()`
### Fixed
1. temp is always zero
2. configuration always zero (zero is correct, need to modify packet definition)
### Known Issues
1. program go to hardfault handler if using while (1) to do UART and I2C tranction

-----------------------------------
## BT-Gyro v0.3.2 (2023.06.27) @master
### New
1. create `Temp_RAW` in MPU6050_t
2. store raw temperature value MPU6050_t
3. update raw temperature data into packet

-----------------------------------
## BT-Gyro v0.3.1 (2023.06.26) @master
### New
- integrate MPU6050 and HM11
- test with MPU6050 and HM11
-----------------------------------
## BT-Gyro v0.3.0 (2023.06.26) @master
### New
- create Hm11_Init()

-----------------------------------
## BT-Gyro v0.2.1 (2023.06.26) @master
### New
- create HM11.h, HM11.c, and HM11_ut.c
  
-----------------------------------
## BT-Gyro v0.2.0 (2023.06.26) @master
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
## BT-Gyro v0.1.3 (2023.06.26) @master
### New
1. receive data into rx buffer 
2. set timeout for `i2c_wait_complete()`
### Notes
1. write_read is basiclly == write + read

-----------------------------------
## BT-Gyro v0.1.2 (2023.06.21) @master
### Fixed
1. fix device didn’t response to commands (issue #3)

-----------------------------------
## BT-Gyro v0.1.1 (2023.06.20) @master
### New
1. include "m2sxxx.h" in "i2c_interrupt.c"
### Changed
1. rename `g_i2C_inst_0` to `g_core_i2c0`
### Fixed
1. fix code jumps into `I2C_enable_irq()` (issue #1)
2. fix no signal while using `I2C_write()` (issue #2)

-----------------------------------
## BT-Gyro v0.1.0 (2023.06.19) @master
### Changed
1. rename `MPU6050_config_t mpu6050_config `related usage to `Mpu6050_Config_t Mpu6050_Config_`
2. comment out unuse STM32 related functions
3. rename all `i2c_MPU6050_write_reg` and `i2c_MPU6050_read_reg` `i2c_MPU6050_write` to `i2c_MPU6050_read` in .c file
### Fixed
1. fix all errors while building project

-----------------------------------
## BT-Gyro v0.0.2 (2023.06.19) @master
### New
1. create corei2c_driver.h
### Changed
1. modify i2c_MPU6050_write_reg for SF2
2. modify i2c_MPU6050_read_reg for SF2

-----------------------------------
## BT-Gyro v0.0.1 (2023.06.16) @master
### New
1. create `Mpu6050_Init()`
2. import mpu6050.h from [MPU6050_driver](https://github.com/anasvag575/MPU6050_driver.git)
3. import mpu6050.c from [MPU6050_driver](https://github.com/anasvag575/MPU6050_driver.git)
### Reference
1. [MPU6050_driver](https://github.com/anasvag575/MPU6050_driver.git)
