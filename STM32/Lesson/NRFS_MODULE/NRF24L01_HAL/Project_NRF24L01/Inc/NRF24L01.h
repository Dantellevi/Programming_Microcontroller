#ifndef __NRF24L01_H__
#define __NRF24L01_H__

#include "main.h"
#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_gpio_ex.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_spi.h"


typedef enum
{
		NRF_CONFIG      = 0x00,//'Config' register address
    NRF_EN_AA       = 0x01,//'Enable Auto Acknowledgment' register address
    NRF_EN_RXADDR   = 0x02,//'Enabled RX addresses' register address
    NRF_SETUP_AW    = 0x03,//'Setup address width' register address
    NRF_SETUP_RETR  = 0x04,//'Setup Auto. Retrans' register address
    NRF_RF_CH       = 0x05,//'RF channel' register address
    NRF_RF_SETUP    = 0x06,//'RF setup' register address
    NRF_STATUS      = 0x07,//'Status' register address
    NRF_OBSERVE_TX  = 0x08,
    NRF_CD          = 0x09,
    NRF_RX_ADDR_P0  = 0x0A,
    NRF_RX_ADDR_P1  = 0x0B,
    NRF_RX_ADDR_P2  = 0x0C,
    NRF_RX_ADDR_P3  = 0x0D,
    NRF_RX_ADDR_P4  = 0x0E,
    NRF_RX_ADDR_P5  = 0x0F,
    NRF_TX_ADDR     = 0x10,
    NRF_RX_PW_P0    = 0x11,//'RX payload width, pipe0' register address
    NRF_RX_PW_P1    = 0x12,//'RX payload width, pipe1' register address
    NRF_RX_PW_P2    = 0x13,//'RX payload width, pipe2' register address
    NRF_RX_PW_P3    = 0x14,//'RX payload width, pipe3' register address
    NRF_RX_PW_P4    = 0x15,//'RX payload width, pipe4' register address
    NRF_RX_PW_P5    = 0x16,//'RX payload width, pipe5' register address
    NRF_FIFO_STATUS = 0x17,//'FIFO Status Register' register address
    NRF_DYNPD       = 0x1C,
    NRF_FEATURE     = 0x1D
	
}NRF24L01_REGISTER;

/* Commands */
typedef enum {
    NRF_CMD_R_REGISTER         = 0x00,
    NRF_CMD_W_REGISTER         = 0x20,
    NRF_CMD_R_RX_PAYLOAD       = 0x61,
    NRF_CMD_W_TX_PAYLOAD       = 0xA0,
    NRF_CMD_FLUSH_TX           = 0xE1,
    NRF_CMD_FLUSH_RX           = 0xE2,
    NRF_CMD_REUSE_TX_PL        = 0xE3,
    NRF_CMD_ACTIVATE           = 0x50,
    NRF_CMD_R_RX_PL_WID        = 0x60,
    NRF_CMD_W_ACK_PAYLOAD      = 0xA8,
    NRF_CMD_W_TX_PAYLOAD_NOACK = 0xB0,
    NRF_CMD_NOP                = 0xFF
} NRF_COMMAND;

/***********Пропускная способность*********/
typedef enum {
    NRF_DATA_RATE_250KBPS = 1,
    NRF_DATA_RATE_1MBPS   = 0,
    NRF_DATA_RATE_2MBPS   = 2
} NRF_DATA_RATE;

/**********Мощность передачи****************/
typedef enum {
    NRF_TX_PWR_M18dBm = 0,
    NRF_TX_PWR_M12dBm = 1,
    NRF_TX_PWR_M6dBm  = 2,
    NRF_TX_PWR_0dBm   = 3
} NRF_TX_PWR;

/************величиа адреса модуля***********/
typedef enum {
    NRF_ADDR_WIDTH_3 = 1,
    NRF_ADDR_WIDTH_4 = 2,
    NRF_ADDR_WIDTH_5 = 3
} NRF_ADDR_WIDTH;


typedef enum { NRF_CRC_WIDTH_1B = 0, NRF_CRC_WIDTH_2B = 1 } NRF_CRC_WIDTH;

typedef enum { NRF_STATE_RX = 1, NRF_STATE_TX = 0 } NRF_TXRX_STATE;

typedef enum { NRF_OK, NRF_ERROR, NRF_INVALID_ARGUMENT } NRF_RESULT;

typedef struct {

    NRF_DATA_RATE  data_rate;
    NRF_TX_PWR     tx_power;
    NRF_CRC_WIDTH  crc_width;
    NRF_ADDR_WIDTH addr_width;

    uint8_t        payload_length;
    uint8_t        retransmit_count;
    uint8_t        retransmit_delay;
    uint8_t        rf_channel;
    const uint8_t* rx_address;
    const uint8_t* tx_address;

    /* Must be sufficient size according to payload_length */
    uint8_t* rx_buffer;

    SPI_HandleTypeDef* spi;
    uint32_t           spi_timeout;

    GPIO_TypeDef* csn_port;
    uint16_t      csn_pin;

    GPIO_TypeDef* ce_port;
    uint16_t      ce_pin;

    GPIO_TypeDef* irq_port;
    uint16_t      irq_pin;

} nrf24l01_config;


typedef struct {
    nrf24l01_config config;

    volatile uint8_t        tx_busy;
    volatile NRF_RESULT     tx_result;
    volatile uint8_t        rx_busy;
    volatile NRF_TXRX_STATE state;

} nrf24l01;

/*****************Функция установки CE****************/
static void CE_SET(nrf24l01 *dev);
/*****************Функция установки CE****************/
static void CE_RESET(nrf24l01 *dev);
/*****************Функция установки CSN****************/
static void CSN_SET(nrf24l01* dev);
/*****************Функция установки CSN****************/
static void CSN_RESET(nrf24l01* dev);
/************************Функция отправки команды**********************************/
NRF_RESULT nrf_send_command(nrf24l01* dev, NRF_COMMAND cmd, const uint8_t* tx,
                            uint8_t* rx, uint8_t len);
/*****************************Функция чтения из регистра******************************/
NRF_RESULT nrf_read_register(nrf24l01* dev, uint8_t reg, uint8_t* data);
/*****************************Функция записи  в регистр регистра******************************/
NRF_RESULT nrf_write_register(nrf24l01* dev, uint8_t reg, uint8_t* data);
/******************Очистка буффера передачи**********************/
NRF_RESULT nrf_flush_tx(nrf24l01* dev);
/******************Очистка буффера приема**********************/
NRF_RESULT nrf_flush_rx(nrf24l01* dev);
/*******************Установка скорости передачи(пропускной способности)*****************************/
NRF_RESULT nrf_set_data_rate(nrf24l01* dev, NRF_DATA_RATE rate) ;
/***********************Установка мощности передачи*******************/
NRF_RESULT nrf_set_tx_power(nrf24l01* dev, NRF_TX_PWR pwr);
NRF_RESULT nrf_set_ccw(nrf24l01* dev, bool activate);
/*********************Функция очистки прерываний************/
NRF_RESULT nrf_clear_interrupts(nrf24l01* dev);











#endif /* __NRF24L01_H__ */


