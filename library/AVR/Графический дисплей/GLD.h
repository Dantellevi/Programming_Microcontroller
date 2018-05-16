


#ifndef GLD_H_
#define GLD_H_

#include "Main.h"
#include <avr/pgmspace.h>
#include <string.h>

#define LCD_PORT PORTA
#define LCD_DDR DDRA
#define LCD_PIN PINA
#define CMD_PORT PORTC
#define CMD_DDR DDRC
#define DI 2
#define RW 3
#define E 4
#define CS1 0
#define CS2 1
#define RST 5
#define CS 0//0 или 1 - в зависимости от уровня которым включается контроллер
#define MODE 0// 0 - белый фон и черная графика, 1 - черный фон и белая графика



#define E_SET				CMD_PORT|=(1<<E)
#define E_RESET				CMD_PORT&=~(1<<E)

#define RW_SET				CMD_PORT|=(1<<RW)
#define RW_RESET			CMD_PORT&=~(1<<RW)

#define RS_SET				CMD_PORT|=(1<<DI)
#define RS_RESET			CMD_PORT&=~(1<<DI)

#define CS1_SET				CMD_PORT|=(1<<CS1)
#define CS1_RESET			CMD_PORT&=~(1<<CS1)

#define CS2_SET				CMD_PORT|=(1<<CS2)
#define CS2_RESSET			CMD_PORT&=~(1<<CS2)


#define RST_SET				CMD_PORT|=(1<<RST)
#define RST_RESSET			CMD_PORT&=~(1<<RST)

#define CS 0//0 или 1 - в зависимости от уровня которым включается контроллер
#define MODE 0// 0 - белый фон и черная графика, 1 - черный фон и белая графика

/*
==========================Функция очистки экрана==================
*/
void KS108_Clear(void);
/*
====================================Функция перехода по координатам================
*/
void KS108_GoToXY(uint8_t x, uint8_t y);

/*
===================================Инициализация дисплея=============================
*/
void KS108_Init(void);

/*
====================================Функция отрисовки пикселя========================
*/
void GLD_Draw_Point(uint8_t x, uint8_t y);
/*
====================Функция определения абсолютного значения переменной===============
			Принимаемые значения:
					int-значения для проверки
			Возращаемое значения:
					int- абсолютное значение

*/
int GLD_abs(int x);
int GLD_sign(int x);

/*
=====================================Функция отрисовки линии===========================
*/
void GLD_Draw_Line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
/*
========================Функция вывода прямоугольника без заливки===========
	x1,y1-координаты нижней левой точки прямоугольник
	x2,y2-координаты верхней правой точки прямоугольника

*/

void GLD_Draw_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);

/*
========================================Функция отрисовки окружности=====================
*/
void GLD_Draw_Ellipse(unsigned char x0, unsigned char y0, unsigned char radius);

/*
==========================Функция прорысовки символа===============
*/
void GLD_printChar(unsigned char x0,unsigned char y0,unsigned char code);

/*
=======================================Функция прорысовки строки =========================
*/
void GLD_print_string(unsigned char x0,unsigned char y0,char* buffer, unsigned char count);

/*
=================================Функция динамического вывода строки====================
*/
void GLD_Printf_String(uint8_t x, uint8_t y, char *str);


#endif /* GLD_H_ */