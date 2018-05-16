#include "i2c.h"

extern uint8_t aTxBuffer[8];
extern uint8_t aSettingBuffer[8];
extern I2C_HandleTypeDef hi2c1;
char str[100];



void I2C_WriteBuffer(uint8_t DEV_ADDR,uint8_t sizebuf)
{
	while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)DEV_ADDR,(uint8_t*) &aTxBuffer, (uint16_t)sizebuf, (uint32_t)1000)!=HAL_OK)
	{
		if(HAL_I2C_GetError(&hi2c1)!=HAL_I2C_ERROR_AF)
		{
			 sprintf(str, "Buffer error");
				LCD_PrintStringXY(str,8,0);
			
		}
	}
}

void SettingDS3231(uint8_t hour,uint8_t min, uint8_t sec)
{
	uint8_t data[3]={0};
	
	data[0]=RTC_ConvertFromBinDec(sec);
	data[1]=RTC_ConvertFromBinDec(min);
	data[2]=RTC_ConvertFromBinDec(hour);
	while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)0x00,(uint8_t*) &data, (uint16_t)sizeof(data), (uint32_t)1000)!=HAL_OK)
	{
		if(HAL_I2C_GetError(&hi2c1)!=HAL_I2C_ERROR_AF)
		{
			 sprintf(str, "Buffer error");
				LCD_PrintStringXY(str,8,0);
			
		}
	}
}






void I2C_ReadBuffer( uint8_t DEV_ADDR, uint8_t sizebuf)
{
	while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)DEV_ADDR, (uint8_t*) &aTxBuffer, (uint16_t)sizebuf, (uint32_t)1000)!=HAL_OK)
	{
		 if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
		 {
			  sprintf(str,"Buffer error");
				LCD_PrintStringXY(str,8,0);
		 }
	}
}

