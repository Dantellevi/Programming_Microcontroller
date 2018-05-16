/*
 * USART.h
 *
 * Created: 11.12.2016 16:26:38
 *  Author: DANTE_L_LEVI
 */ 


#ifndef USART_H_
#define USART_H_

#include "Main.h"

#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 8000000UL
#define  MAX_LINE_LENGHT 40
 void uart_init(unsigned int baud); 		 //инициализация UART'a
 void uart_putc(unsigned char data);		 //отправка одного символа
 unsigned char uart_getc (void);           //получение одного символа
 void uart_write (char *str);              //отправка строки
 void uart_write_int(unsigned int val);    //отправка строки цифр
 char *uart_readln(char *s);			     //функция чтения строки (параметр - указатель на строку)
 int CharToInt(char ch);				     //преобразует цифру (ASCII) в int эквивалент
 void uart_clr(unsigned int l);			 //удаляет l символов
 void uart_wait(char *msg, char k);		//программа ждет нажатия клавиши


#endif /* USART_H_ */