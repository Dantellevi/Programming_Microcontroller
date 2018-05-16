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

#define DDR_COMAND TRISB
#define DDR_DATA   TRISB

#define PORT_COMAND PORTB
#define PORT_DATA   PORTB


#define DDR_RS  TRISB0
#define DDR_RW  TRISB1
#define DDR_E  TRISB2
#define RS  PORTBbits.RB0   
#define RW  PORTBbits.RB1
#define E   PORTBbits.RB2

    
#define D4  PORTBbits.RB4
#define D5  PORTBbits.RB5
#define D6  PORTBbits.RB6
#define D7  PORTBbits.RB7
    

#define E_SET()     (PORTBbits.RB2=1)
#define E_RESET()   (PORTBbits.RB2=0)
#define RS_COM()    (PORTBbits.RB0=0)
#define RS_DATA()   (PORTBbits.RB0=1)


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

