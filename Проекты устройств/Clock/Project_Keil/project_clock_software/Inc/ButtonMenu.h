
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTONMENU_H__
#define __BUTTONMENU_H__

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "stm32f1xx_hal_gpio_ex.h"
#include "stm32f1xx_hal_gpio.h"


/*****************************ПЕРЕЧЕСЛЕНИЕ ДЛЯ ПРОХОДА ПО ПАРАМЕТРАМ ВРЕМЕНИ********************/
typedef enum
{
	CLOCK_SETTING_IDLE,
	CLOCK_SETTING_HOUSE_WAIT,
	CLOCK_SETTING_MINUT_WAIT,
	CLOCK_SETTING_SECOND_WAIT
	
}Clock_Def;


/*************************Функция получения статуса кнопки*****************/
GPIO_PinState ReadButton(uint16_t Btn);

/****************************Функция настройки времени*********************/
void Setting_ClockWatch(uint8_t *h,uint8_t *min,uint8_t *sec);



#endif /* __BUTTONMENU_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



