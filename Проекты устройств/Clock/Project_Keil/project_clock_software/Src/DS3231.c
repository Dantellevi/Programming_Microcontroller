#include "DS3231.h"
extern I2C_HandleTypeDef hi2c1;


/*********************Конвертирования в десятичную***************/
uint8_t RTC_ConverFromDec(uint8_t c)
{
	uint8_t ch = ((c>>4)*10+(0x0F&c));
  return ch;
}

/*********************Конвертирования в двоичнодесятичную***************/
uint8_t RTC_ConvertFromBinDec(uint8_t c)
{
        uint8_t ch = ((c/10)<<4)|(c%10);
        return ch;
}


/***********************Функция задания времени в часы DS3231******************/
void RTC_SetConfig(uint8_t H,uint8_t min, uint8_t sec)
{
	HAL_I2C_Mem_Write(&hi2c1,(uint16_t)0xD0,(uint16_t)0x00,sizeof((uint16_t)0x00),&sec,(uint16_t)sizeof(sec),0x1000);
	HAL_I2C_Mem_Write(&hi2c1,(uint16_t)0xD0,(uint16_t)0x01,sizeof((uint16_t)0x01),&min,(uint16_t)sizeof(min),0x1000);
	HAL_I2C_Mem_Write(&hi2c1,(uint16_t)0xD0,(uint16_t)0x02,sizeof((uint16_t)0x02),&H,(uint16_t)sizeof(H),0x1000);
}












