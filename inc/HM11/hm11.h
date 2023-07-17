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
#define BAUD_VALUE_230400	   26 // 26.12
#define BAUD_VALUE_38400     162 // 161.76
#define BAUD_VALUE_9600      650 // 650.04
#define APRS_BUFF_SIZE       256

/* ----- Buffer Size----- */
#define BLE_TX_BUFF_SIZE 20
#define BLE_RX_BUFF_SIZE 8
#define AT_TX_BUFF_SIZE  8
#define AT_RX_BUFF_SIZE  8

/* ----- Packet Parameters ----- */
#define HEADER_1    0x41
#define HEADER_2    0x58

/* ----- CoreUARTapb instance ----- */
UART_instance_t g_uart_0;


/* ----- Global variables ----- */
uint8_t *_ble_RxBuff_;
int8_t  *_ble_TxBuff_;
uint8_t *_at_RxBuff_;
// uint8_t *_at_TxBuff_;

/* Custom command for HM11. */
typedef enum{
    HM11_RESET = 0x00,      // BLE reset command 
    HM11_TX_ON,             // BLE start transmit command  
    HM11_TX_OFF,            // BLE stop transmit command  
    HM11_SET_TX_FREQ,       // BLE modify transmit frequency
}HM11_COMMAND;


/* ------------------------------
 * Custom packet transmission rate setting.
 * Send data packet in 100, 10, 1 Hz.
 * ------------------------------
 */
typedef enum{
    HM11_TX_RATE_100 = 0x00,    // BLE packet transmission rate 100Hz 
    HM11_TX_RATE_10,            // BLE packet transmission rate 10Hz    
    HM11_TX_RATE_1,             // BLE packet transmission rate 1Hz  
}HM11_TX_RATE;

typedef struct {
    /* HM11 last received command */
    uint8_t last_cmd[8];

    /* Number of packet */
    uint16_t num_packet;

    /* HM11 Tx on/off, set by host command */
    uint8_t onoff;

    /* is HM11 reseting itself */
    uint8_t nrst;

    /* HM11 Tx Frequency, set by host command */
    uint8_t frequency;
    
    /* HM11 number of ticks between packet transmissions */
    uint16_t tx_tick;
  
    /* store the calculate result CRC of received BLE command */
    uint16_t crc_check;
  
} HM11_t;
HM11_t Hm11_;


/* ===== Functions ===== */
/** ---------- Hm11_Init() ----------
 * @brief 
 *      This function initialize the UART instance and
 *      allocate memory for RX/TX buffers. 
 *      Also initialize Hm11_t instance to zero, and initialize default setting for Hm11_t instance.
 * @param
 *      This function doesn't need input parameters
 * @return
 *      This funciion doesn't return
*/
void   Hm11_Init(void);


/** ---------- Hm11_Packet() ----------
 * @brief 
 *      This function packet following information into a packet:
 *      - Header
 *      - 3 axis acceleration
 *      - 3 axis angular velocity
 *      - teameprature
 *      - measurement sensitivity
 *      - number of packet
 *      - CRC8
 * @param
 *      This function doesn't need input parameters
 * @return
 *      This funciion doesn't return
*/
static void Hm11_Packet(void);


/** ---------- Hm11_Is_Rx_Full() ----------
 * @brief 
 *      This function is called by top level main() in a infinity while loop.
 *      This function continous checks whether BLE rx buffer is full (8 bytes), since
 *      command is only 8 byte length. If BLE rx buffer is full, these 8 bytes will
 *      be store into last command. And echo back these received 8 bytes command.
 *      
 * @param
 *      This function doesn't need input parameters
 * @return
 *      This funciion doesn't return
*/
void   Hm11_Is_Rx_Full(void);


/** ---------- Hm11_Config_By_Cmd() ----------
 * @brief 
 *      This function is called by systick handler every systick. 
 *      This function checks if last command is start with 'AX' header, 
 *      and end with correct CRC8.
 *      If so, it config HM11 settings accroding to last command.
 *      It clean the buffer of last command at the end of this function.
 * 
 * @param
 *      This function doesn't need input parameters
 * @return
 *      This funciion doesn't return
*/
static void Hm11_Config_By_Cmd(void);


/** ---------- Hm11_Reset() ----------
 * @brief 
 *      This function is called by Hm11_Config_By_Cmd() every systick. 
 *      If the received command is a reset command, the reset sequence is below:
 *      1. send 'AT':       Disconnect the BLE, HM11 is not able to receive any "AT+" command if BLE is connected
 *      2. send 'AT+NOTI0': Turn off the HM11 nofification while connecting and disconnecting
 *      3. send 'AT+RESET': This command will restart the HM11 module
 *      4. send 'AT+MODE0': Set HM11 to mode0, which doesn't allow "AT+" command through BLE
 * 
 * @param
 *      This function doesn't need input parameters
 * @return
 *      This funciion doesn't return
*/
static void Hm11_Reset(void);


/** ---------- FabricIrq1_IRQHandler() ----------
 * @brief 
 *      This function is called by Cortex M3 coreUARTapb interrupt.
 *      While UART Rx is triggered. This function checks whether nrst is asserted.
 *      If nrst is not asserted ('0'), means HM11 is in reset sequence.
 *      In the mean time, it may receive message from HM11, and the message is not 8-bytes BLE command.
 *      So using AT Rx buffer as UART Rx buffer.
 *      
 *      If nrst in asserted ('1'), HM11 is not in reset sequence.
 *      It is expected the incomming message from UART is BLE command.
 *      In case of incompleted BLE transmission, 
 *      idx indicate the next start address of BLE rx buffer.
 *      idx will be reset to zero if the BLE rx buffer is full (receive all 8 byte of command).
 * 
 * @param
 *      This function doesn't need input parameters
 * @return
 *      This funciion doesn't return
*/
extern void FabricIrq1_IRQHandler(void);


/** ---------- SysTick_Handler() ----------
 * @brief 
 *      This function is called by Cortex M3 every 1 ms.
 *      The tick frequency is 1ms, set by SysTick_Config in MPU6050_Init()
 * 
 *      I2C_system_tick() is also a cortex M3 system function, for I2C timeout.
 *      The I2C timeout interval set here is 1 ms. This value shall same as systick interval.
 *      
 *      Update HM11 settings that set by BLE command.
 *      Which means the HM11 settings is update every 1ms, 
 *      any other BLE command sent within 1 ms will be discarded.
 * 
 *      It checks whether packet transmission frequency is changed by command.
 *      If so, the number of packet will be reset to zero.
 * 
 *      Then if BLE tx buffer is created, and send packet if the HM11 setting is TX ON.
 * 
 * @param
 *      This function doesn't need input parameters
 * @return
 *      This funciion doesn't return
*/
extern void SysTick_Handler(void);


/** ---------- Delay() ----------
 * @brief 
 *      This function is called by Hm11_Reset().
 *      Waiting UART transmission is completed before send next "AT+" command
 * 
 * @param
 *      This function doesn't need input parameters
 * @return
 *      This funciion doesn't return
*/
inline static void Delay(void);

#endif
