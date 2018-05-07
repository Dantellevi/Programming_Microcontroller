
#ifndef LCD_H_
#define LCD_H_


#include "Main.h"



#define DDR_DATA		DDRC
#define PORT_DATA		PORTC
#define PIN_DATA		PINC

#define DDR_COMMAND		DDRC
#define PORT_COMMAND	PORTC

#define RS				PC0	
#define RW				PC1
#define E				PC2

#define D4				PC4
#define D5				PC5
#define D6				PC6
#define D7				PC7

#define E_SET()		(PORTC|=(1<<E))
#define E_RESET()	(PORTC&=~(1<<E))

#define RS_COM()		(PORTC&=~(1<<RS))
#define RS_DATA()		(PORTC|=(1<<RS))

//=========================Command===========================
#define cursor_Mer	0xF0



/*
=======================������� �������� ������ � ����������======================
*/
void LCD_SendData(uint8_t data);
/*
=============================������� �������� �������=============================
*/
void LCD_SendCommand(uint8_t com);
/*
======================������� ������������� �������==============
*/
void LCD_Init(void);
/*
===========================������� ������ �������======================
*/
void Lcd_Print_char(char data);

/*
====================������� ������ ������========================
*/
void Lcd_PrintString(char *str);

/*
=======================������� ������� �������=========================
*/
void Lcd_Clear(void);

/*
================================������� �������� �� ������� � ���������=====================
*/
void lcd_gotoxy(char x, char y);
/*
===============================������� ������ ������ �� �����������==========================
*/
void LCD_printStringXY(char *str,uint8_t x,uint8_t y);
//===================================================================================================================================



#endif /* LCD_H_ */