/* 
 * File:   KS108.h
 * Author: Dante_L_Levi
 *
 * Created on 29 марта 2018 г., 19:37
 */

#ifndef KS108_H
#define	KS108_H

#include "Main.h"

#define GLD_PORT    PORTD
#define GLD_TRIS    TRISD

#define CMD_PORT    PORTB
#define CMD_TRIS    TRISB

#define TRIS_DI     TRISBbits.TRISB4
#define TRIS_RW     TRISBbits.TRISB5
#define TRIS_E      TRISBbits.TRISB3
#define TRIS_CS1    TRISBbits.TRISB0
#define TRIS_CS2    TRISBbits.TRISB1
#define TRIS_RST    TRISBbits.TRISB2




#define DI_SET PORTBbits.RB4=1
#define DI_RESET PORTBbits.RB4=0

    
#define RW_SET PORTBbits.RB5=1
#define RW_RESET PORTBbits.RB5=0
    
#define E_SET PORTBbits.RB3=1
#define E_RESET PORTBbits.RB3=0
    

#define CS1_SET PORTBbits.RB0=1
#define CS1_RESET PORTBbits.RB0=0

#define CS2_SET PORTBbits.RB1=1
#define CS2_RESET PORTBbits.RB1=0
    
 
#define RST_SET PORTBbits.RB2=1
#define RST_RESET PORTBbits.RB2=0

    
#define CS  0   //0 или 1 - в зависимости от уровня которым включается контроллер
#define MODE    1   // 0 - белый фон и черная графика, 1 - черный фон и белая графика

    
 //=======================================================================


/*
======================Функция передачи команды на дисплей===============
			Принимаемые данные :
				unsigned char -значение команды для передачи
*/
void GLDKS108_SendCommand(unsigned char command);

/*
============Функция передачи данных в контроллер дисплея==============
			Принимаемые параметры:
				unsigned char- данные для передачи
*/
void GLDKS108_SendData(unsigned char data);

//=======================================Функция очистки дисплея===================
void GLDKS108_Clear(void);


/*
=============================Инициализация дисплея==============================
*/
void GLDKS108_Init(void);

/*
===============================Функция перехода на строку и столбец==============
			Принимаемые параметры:
			unsigned char-координата х
			unsigned char-координата y
*/
void GLDKS108_GotoXY(unsigned char x, unsigned char y);

/*
========================Функция вывода круга===========
	unsigned char x0-координата х цента,
 *  unsigned char y0-координата у цента, 
 * unsigned char radius- радиус круга
*/
void GLD_Draw_Ellipse(unsigned char x0, unsigned char y0, unsigned char radius);

/*
========================Функция вывода прямоугольника без заливки===========
	x1,y1-координаты нижней левой точки прямоугольник
	x2,y2-координаты верхней правой точки прямоугольника
*/

void GLD_Draw_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);

/*
==========================================Функция отрисовки линии=========================
				Принимаемые значения:
				x1,y1- координаты первой точки линии
				x2,y2-координаты второй точки линии
*/

void GLD_Draw_Line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);

int GLD_sign(int x);
int GLD_abs(int x);

/*
==================================Функция отрисовки точки==============================
				Принимаемые параметры:
				unsigned char-координата х
				unsigned char-координата y
				
*/
void GLD_Draw_Point(unsigned char x, unsigned char y);

/*
=================================Функция вывода символа на дисплей================
			Принимаемые параметры:
				x0,y0-координаты
				code-коде символа
*/
void GLD_printChar(unsigned char x0,unsigned char y0,unsigned char code);


/*
 * ==========================Функция вывода строки==========
 * unsigned char x0-координата х для вывода строки,
 * unsigned char y0-координата у для вывода строки,
 * char* buffer- строка символов для вывода на дисплей, 
 * unsigned char count- размер строки
 */
void GLD_print_string(unsigned char x0,unsigned char y0,char* buffer, unsigned char count);


/*
==================================Функция отрисовки точки==============================
				Принимаемые параметры:
				unsigned char-координата х
				unsigned char-координата y
				
*/
void GLD_Draw_Point(unsigned char x, unsigned char y);

#endif	/* KS108_H */

