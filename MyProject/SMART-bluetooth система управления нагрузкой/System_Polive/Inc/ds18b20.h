

#ifndef __DS18B20_H
#define __DS18B20_H
 
 
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"


#define SKIP_ROM 0
#define NO_SKIP_ROM 1

#define RESOLUTION_9BIT 0x1F
#define RESOLUTION_10BIT 0x3F
#define RESOLUTION_11BIT 0x5F
#define RESOLUTION_12BIT 0x7F



void port_init(void);
//------------------------Функция инициализации ------------------------
//mode-флаг определяющий работаем с 1 датчиком или несколькими
uint8_t ds18b20_init(uint8_t mode);


#endif /* __DS18B20_H */



