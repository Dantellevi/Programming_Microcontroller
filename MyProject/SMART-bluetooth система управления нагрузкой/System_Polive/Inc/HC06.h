

#ifndef __HC06_H
#define __HC06_H
 
 
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"


#define TESTCOMMAND 				"AT"
#define GetVersion					"AT+VERSION"
#define SetSpeed						"AT+BAUD"
#define SetName							"AT+NAME"
#define SetPIN							"AT+PIN"
#define OFF__ParityBit			"AT+PN"
#define	ON_ParityBit				"AT+PO"

#define SPEED9600						"4"
#define SPEED115200					"8"
#define SPEED230400					"9"


//=======================================Прототпы функций=========================
/*
==============================Функция отправки простых команд=====================
*/
void GetResponseATCommand(char *command,char *ResponseBuffer,uint8_t RessieveSize);

//=======================Функция передачи данных===========================
void TransmitData(char *str,uint8_t length);

#endif /* __HC06_H */



