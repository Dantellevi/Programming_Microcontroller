#include "DS3231.h"


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










