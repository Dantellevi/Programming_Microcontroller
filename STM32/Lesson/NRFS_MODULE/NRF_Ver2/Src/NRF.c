#include "NRF.h"

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;



#define TX_ADR_WIDTH 			3
#define TX_PLOAD_WIDTH 		5
uint8_t TX_ADRESS[TX_ADR_WIDTH]={0xb3,0xb4,0x01};
uint8_t RX_BUF[TX_PLOAD_WIDTH]={0};

extern char str1[50];

uint8_t ErrCnt_F1=0;


/*********************Функция микрозадержки******************/
__STATIC_INLINE void DelayMicro(__IO uint32_t micros)
{
	micros*=(SystemCoreClock/1000000)/9;
	
	while(micros--);
}


/***********************Функция чтения данных из регистра **********************************/
uint8_t NRF24_ReadReg(uint8_t addr)
{
	uint8_t dt=0,cmd;
	CS_ON;
	HAL_SPI_TransmitReceive(&hspi1,&addr,&dt,1,1000);
	if(addr!=STATUS)//если адрес равен адрес регистра статуса то возращаем его
	{
		
	}
	CS_OFF;
	return dt;
	
}



/************************Функция записи в регистр*************************/
void NRF24_WriteReg(uint8_t addr,uint8_t dt)
{
	addr|=W_REGISTER;//вкл. бит записи в адрес
	
	CS_ON;
	HAL_SPI_Transmit(&hspi1,&addr,1,1000);//записываем адрес
	HAL_SPI_Transmit(&hspi1,&dt,1,1000);//записываем данные
	CS_OFF;
}


void NRF24_ToggleFeatures(void)
{
	uint8_t dt[1]={ACTIVATE};
	CS_ON;
	HAL_SPI_Transmit(&hspi1,dt,1,1000);
	DelayMicro(1);
	dt[0]=0x73;
	HAL_SPI_Transmit(&hspi1,dt,1,1000);
	CS_OFF;
	
	
}

/************************Запись данных в буффер*************************/
void NRF24_Write_Buf(uint8_t addr,uint8_t *pBuf, uint8_t bytes)
{
	addr|=W_REGISTER;//вкл. бит записи в адрес
	CS_ON;
	HAL_SPI_Transmit(&hspi1,&addr,1,1000);//записываем адрес
	HAL_SPI_Transmit(&hspi1,pBuf,bytes,1000);//записываем данные
	CS_OFF;
}



/************************Чтение данных из буффер*************************/
void NRF24_Read_Buf(uint8_t addr,uint8_t *pBuf, uint8_t bytes)
{
	
	CS_ON;
	HAL_SPI_Transmit(&hspi1,&addr,1,1000);//записываем адрес
	HAL_SPI_Receive(&hspi1,pBuf,bytes,1000);//записываем данные
	CS_OFF;
}




