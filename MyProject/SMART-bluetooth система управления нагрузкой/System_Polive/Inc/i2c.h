

#ifndef __I2C_H
#define __I2C_H
 
 
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"


void I2C_WriteBuffer(uint8_t DEV_ADDR,uint8_t sizebuf);
void I2C_ReadBuffer( uint8_t DEV_ADDR, uint8_t sizebuf);
void SettingDS3231(uint8_t hour,uint8_t min, uint8_t sec);

#endif /* __I2C_H */



