
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LEDLIB_H__
#define __LEDLIB_H__

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdint.h"



#define cs_set() HAL_GPIO_WritePin(CS_LED_GPIO_Port, CS_LED_Pin, GPIO_PIN_RESET)
#define cs_reset() HAL_GPIO_WritePin(CS_LED_GPIO_Port, CS_LED_Pin, GPIO_PIN_SET)
#define cs_strob() cs_reset();cs_set()





/***********************Отправка данных в MAX7219******************/
void Send_MAX7219(uint8_t rg,uint8_t dt);
/*********************Очистка индикатора*******************/
void Clear_MAX7219(void);
/*********************Очистка индикатора*******************/
void Clear_MAX7219(void);
/*************************Функция вывода числа на дисплей************/
void Number_MAX7219(volatile long n);
/****************************Функция вывода значений часов ******************/
void Print_ValClock(uint8_t h,uint8_t min,uint8_t sec);
/***********************Функция инициализации дисплея**************************/
void Init_7219(void);





#endif /* __LEDLIB_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



