#include "ButtonMenu.h"

Clock_Def Btn_setting=CLOCK_SETTING_IDLE;

/*
#define CS_LED_Pin GPIO_PIN_4
#define CS_LED_GPIO_Port GPIOA
#define Right_B_Pin GPIO_PIN_13
#define Right_B_GPIO_Port GPIOB
#define Count_B_Pin GPIO_PIN_14
#define Count_B_GPIO_Port GPIOB
#define Select_B_Pin GPIO_PIN_15
#define Select_B_GPIO_Port GPIOB
#define Left_B_Pin GPIO_PIN_8
#define Left_B_GPIO_Port GPIOA

*/

/*************************Функция получения статуса кнопки*****************/
GPIO_PinState ReadButton(uint16_t Btn)
{
	switch(Btn)
	{
		
		case Right_B_Pin:
		{
			if(HAL_GPIO_ReadPin(Right_B_GPIO_Port,Right_B_Pin)==GPIO_PIN_SET)
				return GPIO_PIN_SET;
			else 
				return GPIO_PIN_RESET;
			
		}
		case Count_B_Pin:
		{
			if(HAL_GPIO_ReadPin(Count_B_GPIO_Port,Count_B_Pin)==GPIO_PIN_SET)
				return GPIO_PIN_SET;
			else 
				return GPIO_PIN_RESET;
			
		}
		case Select_B_Pin:
		{
			if(HAL_GPIO_ReadPin(Select_B_GPIO_Port,Select_B_Pin)==GPIO_PIN_SET)
				return GPIO_PIN_SET;
			else 
				return GPIO_PIN_RESET;
			
		}
		case Left_B_Pin:
		{
			if(HAL_GPIO_ReadPin(Left_B_GPIO_Port,Left_B_Pin)==GPIO_PIN_SET)
				return GPIO_PIN_SET;
			else 
				return GPIO_PIN_RESET;
			
		}
		
		default:
		{
			return GPIO_PIN_RESET;
		}
	}
	
}


/****************************Функция настройки времени*********************/
void Setting_ClockWatch(uint8_t *h,uint8_t *min,uint8_t *sec)
{
	Btn_setting=CLOCK_SETTING_HOUSE_WAIT;
	
	switch(Btn_setting)
	{
		case CLOCK_SETTING_HOUSE_WAIT:
		{
			//если нажата кнопка переходим на настройку минут
			if(ReadButton(Right_B_Pin)==GPIO_PIN_SET)
			{
				Btn_setting=CLOCK_SETTING_MINUT_WAIT;
			}
			//переходим на секунды
			else if(ReadButton(Left_B_Pin)==GPIO_PIN_SET)
			{
				Btn_setting=CLOCK_SETTING_MINUT_WAIT;
			}
			else if(ReadButton(Count_B_Pin)==GPIO_PIN_SET)
			{
				*h+=1;
				if(*h>23)
				{
					*h=0;
				}
			}
			
			break;
		}
		
		case CLOCK_SETTING_MINUT_WAIT:
		{
			//если нажата кнопка переходим на настройку минут
			if(ReadButton(Right_B_Pin)==GPIO_PIN_SET)
			{
				Btn_setting=CLOCK_SETTING_SECOND_WAIT;
			}
			//переходим на секунды
			else if(ReadButton(Left_B_Pin)==GPIO_PIN_SET)
			{
				Btn_setting=CLOCK_SETTING_HOUSE_WAIT;
			}
			else if(ReadButton(Count_B_Pin)==GPIO_PIN_SET)
			{
				*min+=1;
				if(*min>59)
				{
					*min=0;
				}
			}
			
			break;
		}
		
		case CLOCK_SETTING_SECOND_WAIT:
		{
			//если нажата кнопка переходим на настройку минут
			if(ReadButton(Right_B_Pin)==GPIO_PIN_SET)
			{
				Btn_setting=CLOCK_SETTING_HOUSE_WAIT;
			}
			//переходим на секунды
			else if(ReadButton(Left_B_Pin)==GPIO_PIN_SET)
			{
				Btn_setting=CLOCK_SETTING_MINUT_WAIT;
			}
			else if(ReadButton(Count_B_Pin)==GPIO_PIN_SET)
			{
				*sec+=1;
				if(*sec>59)
				{
					*sec=0;
				}
			}
			
			break;
		}
		
		
	}
	
	//Функция задания времени в ds3231
	
	
}




