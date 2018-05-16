


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
#define CS 0//0 ��� 1 - � ����������� �� ������ ������� ���������� ����������
#define MODE 0// 0 - ����� ��� � ������ �������, 1 - ������ ��� � ����� �������



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

#define CS 0//0 ��� 1 - � ����������� �� ������ ������� ���������� ����������
#define MODE 0// 0 - ����� ��� � ������ �������, 1 - ������ ��� � ����� �������

/*
==========================������� ������� ������==================
*/
void KS108_Clear(void);
/*
====================================������� �������� �� �����������================
*/
void KS108_GoToXY(uint8_t x, uint8_t y);

/*
===================================������������� �������=============================
*/
void KS108_Init(void);

/*
====================================������� ��������� �������========================
*/
void GLD_Draw_Point(uint8_t x, uint8_t y);
/*
====================������� ����������� ����������� �������� ����������===============
			����������� ��������:
					int-�������� ��� ��������
			����������� ��������:
					int- ���������� ��������

*/
int GLD_abs(int x);
int GLD_sign(int x);

/*
=====================================������� ��������� �����===========================
*/
void GLD_Draw_Line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
/*
========================������� ������ �������������� ��� �������===========
	x1,y1-���������� ������ ����� ����� �������������
	x2,y2-���������� ������� ������ ����� ��������������

*/

void GLD_Draw_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);

/*
========================================������� ��������� ����������=====================
*/
void GLD_Draw_Ellipse(unsigned char x0, unsigned char y0, unsigned char radius);

/*
==========================������� ���������� �������===============
*/
void GLD_printChar(unsigned char x0,unsigned char y0,unsigned char code);

/*
=======================================������� ���������� ������ =========================
*/
void GLD_print_string(unsigned char x0,unsigned char y0,char* buffer, unsigned char count);

/*
=================================������� ������������� ������ ������====================
*/
void GLD_Printf_String(uint8_t x, uint8_t y, char *str);


#endif /* GLD_H_ */