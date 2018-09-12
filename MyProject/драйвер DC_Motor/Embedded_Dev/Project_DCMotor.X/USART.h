#ifndef USART_H
#define	USART_H


#include "Main.h"



/*----------------Функция инициализации UART интерфейса-------------------*/
void Usart_Init(int32_t baud);
/*-----------------Функция передачи символа по USART--------------*/
void Transmit_char(char data);

/*--------------------Функция проверки флага передачи-------------*/
char UART_TX_Emty(void);

/*------------------Функция вывода строки в терминал----------*/
void Uart_PrintString(char *buffer);

/*---------------------Функция считывания одиночного символа----------*/
char Uart_Read(void);
/*-------------------Функция приема строки из терминал-----------*/
void Ressieve_String(char *buffer,uint16_t length);



#endif	/* USART_H */

