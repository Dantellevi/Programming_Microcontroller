#include "NRF24L01.h"

/*****************Функция установки CE****************/
static void CE_SET(nrf24l01 *dev)
{
	HAL_GPIO_WritePin(dev->config.ce_port, dev->config.ce_pin, GPIO_PIN_SET);
}

/*****************Функция установки CE****************/
static void CE_RESET(nrf24l01 *dev)
{
	HAL_GPIO_WritePin(dev->config.ce_port, dev->config.ce_pin, GPIO_PIN_RESET);
}

/*****************Функция установки CSN****************/
static void CSN_SET(nrf24l01* dev) 
{
    HAL_GPIO_WritePin(dev->config.csn_port, dev->config.csn_pin, GPIO_PIN_SET);
}
/*****************Функция установки CSN****************/
static void CSN_RESET(nrf24l01* dev) 
{
    HAL_GPIO_WritePin(dev->config.csn_port, dev->config.csn_pin,
                      GPIO_PIN_RESET);
}

/************************Функция отправки команды**********************************/
NRF_RESULT nrf_send_command(nrf24l01* dev, NRF_COMMAND cmd, const uint8_t* tx,
                            uint8_t* rx, uint8_t len)
{
	uint8_t myTX[len+1];
	uint8_t myRX[len+1];
	myTX[0]=cmd;
	
	int i=0;
	for(i=0;i<len;i++)
	{
		myTX[1+i]=tx[i];
		 myRX[i]     = 0;
		
	}
	CSN_RESET(dev);
	if (HAL_SPI_TransmitReceive(dev->config.spi, myTX, myRX, 1 + len,
                                dev->config.spi_timeout) != HAL_OK)
	{
    return NRF_ERROR;
  }
	for(i=0;i<len;i++)
	{
		rx[i]=myRX[1+i];
	}
	CSN_SET(dev);
	
}

/*****************************Функция чтения из регистра******************************/
NRF_RESULT nrf_read_register(nrf24l01* dev, uint8_t reg, uint8_t* data)
{
	uint8_t tx=0;
	if (nrf_send_command(dev, NRF_CMD_R_REGISTER | reg, &tx, data, 1) !=
        NRF_OK)
	{
		
		return NRF_ERROR;
	}
	return NRF_OK;
}

/*****************************Функция записи  в регистр регистра******************************/
NRF_RESULT nrf_write_register(nrf24l01* dev, uint8_t reg, uint8_t* data)
{
    uint8_t rx = 0;
	
    if (nrf_send_command(dev, NRF_CMD_W_REGISTER | reg, data, &rx, 1) !=
        NRF_OK)
      {
        return NRF_ERROR;
			}
    return NRF_OK;
}

/******************Очистка буффера передачи**********************/
NRF_RESULT nrf_flush_tx(nrf24l01* dev)
{
    uint8_t rx = 0;
    uint8_t tx = 0;
    if (nrf_send_command(dev, NRF_CMD_FLUSH_TX, &tx, &rx, 0) != NRF_OK) {
        return NRF_ERROR;
    }
    return NRF_OK;
}

/******************Очистка буффера приема**********************/
NRF_RESULT nrf_flush_rx(nrf24l01* dev)
{
    uint8_t rx = 0;
    uint8_t tx = 0;
    if (nrf_send_command(dev, NRF_CMD_FLUSH_RX, &tx, &rx, 0) != NRF_OK) {
        return NRF_ERROR;
    }
    return NRF_OK;
}

/*******************Установка скорости передачи(пропускной способности)*****************************/
NRF_RESULT nrf_set_data_rate(nrf24l01* dev, NRF_DATA_RATE rate) 
{
    uint8_t reg = 0;
    if (nrf_read_register(dev, NRF_RF_SETUP, &reg) != NRF_OK) {
        return NRF_ERROR;
    }
    if (rate & 1) { // low bit set
        reg |= 1 << 5;
    } else { // low bit clear
        reg &= ~(1 << 5);
    }

    if (rate & 2) { // high bit set
        reg |= 1 << 3;
    } else { // high bit clear
        reg &= ~(1 << 3);
    }
    if (nrf_write_register(dev, NRF_RF_SETUP, &reg) != NRF_OK) {
        return NRF_ERROR;
    }
    dev->config.data_rate = rate;
    return NRF_OK;
}


/***********************Установка мощности передачи*******************/
NRF_RESULT nrf_set_tx_power(nrf24l01* dev, NRF_TX_PWR pwr)
{
    uint8_t reg = 0;
    if (nrf_read_register(dev, NRF_RF_SETUP, &reg) != NRF_OK) {
        return NRF_ERROR;
    }
    reg &= 0xF9;     // clear bits 1,2
    reg |= pwr << 1; // set bits 1,2
    if (nrf_write_register(dev, NRF_RF_SETUP, &reg) != NRF_OK) {
        return NRF_ERROR;
    }
    dev->config.tx_power = pwr;
    return NRF_OK;
}


NRF_RESULT nrf_set_ccw(nrf24l01* dev, bool activate)
	{
    uint8_t reg = 0;
    if (nrf_read_register(dev, NRF_RF_SETUP, &reg) != NRF_OK) {
        return NRF_ERROR;
    }

    if (activate) {
        reg |= 0x80;
    } else {
        reg &= 0x7F;
    }

    if (nrf_write_register(dev, NRF_RF_SETUP, &reg) != NRF_OK) {
        return NRF_ERROR;
    }
    return NRF_OK;
}

/*********************Функция очистки прерываний************/
NRF_RESULT nrf_clear_interrupts(nrf24l01* dev)
{
    uint8_t reg = 0;
    if (nrf_read_register(dev, NRF_STATUS, &reg) != NRF_OK) {
        return NRF_ERROR;
    }

    reg |= 7 << 4; // setting bits 4,5,6

    if (nrf_write_register(dev, NRF_STATUS, &reg) != NRF_OK) {
        return NRF_ERROR;
    }
    return NRF_OK;
}


