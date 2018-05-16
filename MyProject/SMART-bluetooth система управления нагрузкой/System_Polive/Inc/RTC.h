

#ifndef __RTC_H
#define __RTC_H
 
 
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"


uint8_t RTC_ConvertFromDec(uint8_t c); //перевод двоично-десятичного числа в десятичное
uint8_t RTC_ConvertFromBinDec(uint8_t c); //перевод десятичного числа в двоично-десятичное

#endif /* __RTC_H */



