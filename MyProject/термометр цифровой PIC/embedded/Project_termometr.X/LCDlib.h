/* 
 * File:   LCDlib.h
 * Author: Dante_L_Levi
 *
 * Created on 25 апреля 2018 г., 21:55
 */

#ifndef LCDLIB_H
#define	LCDLIB_H

#include "Main.h"
#include <string.h>

#define DDR_COMAND TRISA
#define DDR_DATA   TRISB

#define PORT_COMAND PORTA
#define PORT_DATA   PORTB


#define DDR_RS  TRISA0
#define DDR_RW  TRISA1
#define DDR_E  TRISA2
#define RS  PORTAbits.RA0   
#define RW  PORTAbits.RA1
#define E   PORTAbits.RA2

    
#define D4  PORTBbits.RB4
#define D5  PORTBbits.RB5
#define D6  PORTBbits.RB6
#define D7  PORTBbits.RB7
    

#define E_SET()     (PORTAbits.RA2=1)
#define E_RESET()   (PORTAbits.RA2=0)
#define RS_COM()    (PORTAbits.RA0=0)
#define RS_DATA()   (PORTAbits.RA0=1)


//====================Прототипы функций==========

/*
 ==========================Функция инициализации===========
 */
void LCD_Init(char lcd);
/*
 ==========================Функция вывода символа на дисплей==============
 */
void LCD_PrintChar(char c);
/*
 ==================Функция вывода строки символов========
 */
void LCD_PrintString(char *str);
/*
 ================Функция перехода по строкам =======
 */
void LCD_GoToXY(uint8_t x,uint8_t y);
/*
 ===========Функция печати строки по координатам========
 */
void LCD_PrintStringXY(char *str,char x,char y);
/*
 ==================Функция очистки дисплея===========
 */
void LCD_Clear(void);

void Print_int(uint16_t data,uint8_t x,uint8_t y);


#endif	/* LCDLIB_H */

