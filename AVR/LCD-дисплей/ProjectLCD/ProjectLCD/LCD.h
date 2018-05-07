
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
=======================Функция передачи данных в контроллер======================
*/
void LCD_SendData(uint8_t data);
/*
=============================Функция передачи команды=============================
*/
void LCD_SendCommand(uint8_t com);
/*
======================Функция инициализации дисплея==============
*/
void LCD_Init(void);
/*
===========================Функция вывода символа======================
*/
void Lcd_Print_char(char data);

/*
====================Функция печати строки========================
*/
void Lcd_PrintString(char *str);

/*
=======================Функция очистки дисплея=========================
*/
void Lcd_Clear(void);

/*
================================Функция перехода по строкам и столбцами=====================
*/
void lcd_gotoxy(char x, char y);
/*
===============================Функция печати строки по координатам==========================
*/
void LCD_printStringXY(char *str,uint8_t x,uint8_t y);
//===================================================================================================================================



#endif /* LCD_H_ */