#include "HC06.h"

extern UART_HandleTypeDef huart1;

/*
==============================Функция отправки простых команд=====================
*/
void GetResponseATCommand(char *command,char *ResponseBuffer,uint8_t RessieveSize)
{
	HAL_UART_Transmit(&huart1,(uint8_t *)command,strlen(command),0x1000);
	HAL_UART_Receive_IT(&huart1,(uint8_t *)ResponseBuffer,RessieveSize);
}



//=======================Функция передачи данных===========================
void TransmitData(char *str,uint8_t length)
{
	HAL_UART_Transmit(&huart1,(uint8_t *)str,strlen(str),0x1000);
}

