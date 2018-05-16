/* 
 * File:   USART.h
 * Author: Dante_L_Levi
 *
 * Created on 4 февраля 2018 г., 17:27
 */

#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "Main.h"
    
    
 //=======================================Прототипы функций=====================
 char USART_Init(long int baud);   //Инициализация USART
 void Transmit_char(char data);     //Передача символа
 char UART_TX_Empty(void);          //Проверка на передачу
 void Usart_PrintString(char *Text);    //Передачи строки
 char UART_Data_Ready();            //Проверка на прием
 void UART_Read_Text(char *Output, unsigned int length);    //Прием строки
 char USART_Read(void);             //Прием символа
 
    
 //=============================================================================


#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

