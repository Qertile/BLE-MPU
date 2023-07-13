#ifndef HM11_H_
#define HM11_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../../firmware/drivers/CoreUARTapb/core_uart_apb.h"
#include "../../firmware/CMSIS/m2sxxx.h"
#include "../CRC8/crc8.h"

/* ----- UART Parameters ----- */
#define COREUARTAPB0_BASE_ADDR   0x50001000
#define BAUD_VALUE_115200    53 // 53.25
#define BAUD_VALUE_230400	 26 // 26.12
#define BAUD_VALUE_38400     162 // 161.76
#define BAUD_VALUE_9600      650 // 650.04
#define APRS_BUFF_SIZE       256

#define BLE_TX_BUFF_SIZE 20
#define BLE_RX_BUFF_SIZE 8

/* ----- Packet Parameters ----- */
#define HEADER_1    0x41
#define HEADER_2    0x58

/* ----- CoreUARTapb instance ----- */
UART_instance_t g_uart_0;


/* ----- Global variables ----- */
uint8_t *_ble_RxBuff_;
int8_t *_ble_TxBuff_;

/* Custom command for HM11. */
typedef enum{
  HM11_RESET = 0x00,    // BLE packet transmission rate 100Hz               //
  HM11_TX_ON,            // BLE packet transmission rate 10Hz                  //
  HM11_TX_OFF,             // BLE packet transmission rate 1Hz                //
  HM11_SET_TX_FREQ,             // BLE packet transmission rate 1Hz
}HM11_COMMAND;


/* Custom packet transmission rate setting.
 * Send data packet in 100, 10, 1 Hz.
 */
typedef enum{
  HM11_TX_RATE_100 = 0x00,    // BLE packet transmission rate 100Hz               //
  HM11_TX_RATE_10,            // BLE packet transmission rate 10Hz                  //
  HM11_TX_RATE_1,             // BLE packet transmission rate 1Hz                //
}HM11_TX_RATE;

typedef struct {
  /* HM11 last received command */
  uint8_t last_cmd[8];

  /* Number of packet */
  uint16_t num_packet;

  /* HM11 Tx on/off, set by host command */
  uint8_t onoff;

  /* HM11 Tx Frequency, set by host command */
  uint8_t frequency;
  uint16_t tx_tick;
  
  
} HM11_t;
HM11_t Hm11_;

/* ----- Functions ----- */
void Hm11_Packet(void);
void Hm11_Init(void);
void Hm11_Is_Rx_Full(void);
void Hm11_Config_By_Cmd(void);

extern void FabricIrq1_IRQHandler(void);
extern void SysTick_Handler(void);



#endif
