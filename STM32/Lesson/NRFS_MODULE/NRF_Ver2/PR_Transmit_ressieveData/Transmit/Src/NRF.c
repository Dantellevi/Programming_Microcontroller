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
		cmd=0xFF;
		HAL_SPI_TransmitReceive(&hspi1,&cmd,&dt,1,1000);
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



/********************Очистка буффера приема*******************************/
void NRF24_FlushRX(void)
{
	uint8_t dt[1]={FLUSH_RX};
	CS_ON;
	HAL_SPI_Transmit(&hspi1,dt,1,1000);
	DelayMicro(1);
	CS_OFF;
}

/********************Очистка буффера передачи*******************************/
void NRF24_FlushTX(void)
{
	uint8_t dt[1]={FLUSH_TX};
	CS_ON;
	HAL_SPI_Transmit(&hspi1,dt,1,1000);
	DelayMicro(1);
	CS_OFF;
}


/**********************Перевод NRF в режим приемника**************************/
void NRF24_RX_MODE(void)
{
	uint8_t regval=0x00;
	regval=NRF24_ReadReg(CONFIG);
	regval|=(1<<PWR_UP)|(1<<PRIM_RX);
	NRF24_WriteReg(CONFIG,regval);
	CE_SET;
	DelayMicro(150);
	NRF24_FlushRX();
	NRF24_FlushTX();
	
}



/**********************Перевод NRF в режим передатчика**************************/
void NRF24_TX_MODE(uint8_t *pBuf)
{
	NRF24_Write_Buf(TX_ADDR,TX_ADRESS,TX_ADR_WIDTH);
	CE_SET;
	//очистка
	NRF24_FlushRX();
	NRF24_FlushTX();
	
}


/********************Передача данных *****************************/
void NRF24_Transmit(uint8_t addr,uint8_t *pBuf,uint8_t Bytes)
{
	CE_RESET;
	CS_ON;
	HAL_SPI_Transmit(&hspi1,&addr,1,1000);
	DelayMicro(1);
	HAL_SPI_Transmit(&hspi1,pBuf,Bytes,1000);
	CS_OFF;
	CE_SET;
}

uint8_t NRF24L01_Send(uint8_t *pBuf)
{
	uint8_t status=0x00 ,regval=0x00;
	NRF24_TX_MODE(pBuf);
	regval=NRF24_ReadReg(CONFIG);
	regval|=(1<<PWR_UP);
	regval&=~(1<<PRIM_RX);
	NRF24_WriteReg(CONFIG,regval);
	DelayMicro(150);
	NRF24_Transmit(WR_TX_PLOAD,pBuf,TX_PLOAD_WIDTH);//отправляем данные из модуля
	CE_SET;
	DelayMicro(15);
	CE_RESET;
	//while((GPIO_PinState)IRQ==GPIO_PIN_SET){}
	HAL_Delay(500);
		status=NRF24_ReadReg(STATUS);
		if(status&TX_DS)//tx_ds==0x20
		{
			LED_TGL;
			NRF24_WriteReg(STATUS,0x20);
		}
		else if(status&MAX_RT)
		{
			NRF24_WriteReg(STATUS,0x10);
			NRF24_FlushTX();
		}
		regval=NRF24_ReadReg(OBSERVE_TX);
		//режим приемника
		NRF24_RX_MODE();
		return regval;
}


/**************************Прием данных****************************/
void NRF24L01_Ressieve(void)
{
	uint8_t status=0x01;
	uint16_t dt=0;
	while((GPIO_PinState)IRQ==GPIO_PIN_SET){}
	status =NRF24_ReadReg(STATUS);
		sprintf(str1,"STATUS: 0x%02X\r\n",status);
		HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
		LED_TGL;
		DelayMicro(10);
		if(status& 0x40)
		{
			NRF24_Read_Buf(RD_RX_PLOAD,RX_BUF,TX_PLOAD_WIDTH);
			dt=*(int16_t*)RX_BUF;
			//выводим 
			char mass[200];
			sprintf(mass,"Ressieve data=%d",dt);
			HAL_UART_Transmit(&huart1,(uint8_t*)mass,strlen(mass),0x1000);
			dt=*(int16_t*)(RX_BUF+2);
			sprintf(mass,"Ressieve data=%d",dt);
			HAL_UART_Transmit(&huart1,(uint8_t*)mass,strlen(mass),0x1000);
		}
	
}






/**********************Инициализация NRF*********************************/
void NRF24_Init(void)
{
	CE_RESET;
	DelayMicro(5000);
	NRF24_WriteReg(CONFIG,0x0a);//Set PWR_UP bit,enable CRC(1Byte)
	DelayMicro(5000);
	NRF24_WriteReg(EN_AA,0x01);//Enable Pipie0
	NRF24_WriteReg(EN_RXADDR,0x01);//Enable Pipie0
	NRF24_WriteReg(SETUP_AW,0x01);//Setup adress width=3 bytes
	NRF24_WriteReg(SETUP_RETR,0x5F);//150us,15 retrnes
	NRF24_ToggleFeatures();
	NRF24_WriteReg(FEATURE,0);
	NRF24_WriteReg(DYNPD,0);
	NRF24_WriteReg(STATUS,0x70);//Reset flags for IRQ
	NRF24_WriteReg(RF_CH,76);//частота 2476МГц
	NRF24_WriteReg(RF_SETUP,0x06);//TX PWR=0 dBm, Datarate:1Mbps
	NRF24_Write_Buf(TX_ADDR,TX_ADRESS,TX_ADR_WIDTH);
	NRF24_Write_Buf(RX_ADDR_P0,TX_ADRESS,TX_ADR_WIDTH);
	NRF24_WriteReg(RX_PW_P0,TX_PLOAD_WIDTH);//number of byte in Rx payload
	
	
	
}












