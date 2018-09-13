#include "LEDLib.h"

uint8_t SPIaTxBuffer[1];
extern SPI_HandleTypeDef hspi1;
char dg=8;


/***********************Отправка данных в MAX7219******************/
void Send_MAX7219(uint8_t rg,uint8_t dt)
{
	cs_set();
	SPIaTxBuffer[0]=rg;
	HAL_SPI_Transmit(&hspi1,(uint8_t *)SPIaTxBuffer,1,5000);
	SPIaTxBuffer[0]=dt;
	HAL_SPI_Transmit(&hspi1,(uint8_t *)SPIaTxBuffer,1,5000);
	cs_reset();
	
	
}


/*********************Очистка индикатора*******************/
void Clear_MAX7219(void)
{
	uint8_t i =dg;
	do
	{
		Send_MAX7219(i,0xF);//символ пустоты
	}while(--i);
	
}

/*************************Функция вывода числа на дисплей************/
void Number_MAX7219(volatile long n)
{
	uint8_t ng=0;//переменная для минуса
	if(n<0)
	{
		ng=1;n*=-1;
	}
	Clear_MAX7219();
	if(n==0)
	{
		Send_MAX7219(0x01,0);
		return;
	}
	
	uint8_t i=0;
	do
	{
		Send_MAX7219(++i,n%10);
		n/=10;
	}while(n);
	
	if(ng)
	{
		Send_MAX7219(i+1,0xA);//символ -
		
	}
	
}

/***********************Функция инициализации дисплея**************************/
void Init_7219(void)
{
  Send_MAX7219(0x09,0xFF);//включим режим декодирования
  Send_MAX7219(0x0B,dg-1);//кол-во используемых разрядов
  Send_MAX7219(0x0A,0x02);//интенсивность свечения
  Send_MAX7219(0x0C,0x01);//включим индикатор
  Clear_MAX7219();

}


/****************************Функция вывода значений часов ******************/
void Print_ValClock(uint8_t h,uint8_t min,uint8_t sec)
{
	uint8_t hl=h%10;
	uint8_t hh;
	if(h>=10)
	{
		hh=h/10;
	}
	else
	{
		hh=0;
	}
	
	uint8_t minL=min%10;
	uint8_t minH;
	if(h>=10)
	{
		minH=min/10;
	}
	else
	{
		minH=0;
	}
	
	uint8_t secL=min%10;
	uint8_t secH;
	
	if(h>=10)
	{
		secH=sec/10;
	}
	else
	{
		secH=0;
	}
	
	Send_MAX7219(1,secL);
	Send_MAX7219(2,secH);
	Send_MAX7219(3,(minL|0x80));
	Send_MAX7219(4,minH);
	Send_MAX7219(5,(hl|0x80));
	Send_MAX7219(6,hh);
	
}



