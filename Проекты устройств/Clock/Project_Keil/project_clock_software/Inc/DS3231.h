
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DS3231_H__
#define __DS3231_H__

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdint.h"

#define ADDR_DS3231 0xD0


/*********************Конвертирования в десятичную***************/
uint8_t RTC_ConverFromDec(uint8_t c);
/*********************Конвертирования в двоичнодесятичную***************/
uint8_t RTC_ConvertFromBinDec(uint8_t c);

#endif /* __DS3231_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



