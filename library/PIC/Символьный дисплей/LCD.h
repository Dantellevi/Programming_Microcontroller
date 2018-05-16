
#ifndef LCD_H
#define	LCD_H

#include "Main.h"

#define DDR_DATA        TRISB
#define PORT_DATA       PORTB

#define DDR_COMMAND     TRISB
#define PORT_COMMAND    PORTB

#define DDR_RS      TRISB0
#define DDR_RW      TRISB1
#define DDR_E       TRISB2

#define DDR_D4      TRISB4
#define DDR_D5      TRISB5
#define DDR_D6      TRISB6
#define DDR_D7      TRISB7



#define RS              PORTBbits.RB0
#define RW              PORTBbits.RB1
#define E               PORTBbits.RB2

#define D4              PORTBbits.RB4
#define D5              PORTBbits.RB5
#define D6              PORTBbits.RB6
#define D7              PORTBbits.RB7

#define E_SET()             E=1
#define E_RESET()           E=0

#define RS_COM()            RS=0
#define RS_DATA()           RS=1

#define D4_set              D4=1
#define D5_set              D5=1
#define D6_set              D6=1
#define D7_set              D7=1

#define D4_reset            D4=0
#define D5_reset            D5=0
#define D6_reset            D6=0
#define D7_reset            D7=0




//======================Command==================
#define OFF_DISPLAY         0x08
#define CLEAR_DISPLAY       0x01
#define Shift_Cursor_R      0x06
#define ON_Display          0x0C



//==============================Прототипы===========

/*
 ===================Функция передачи данных ===========
 */
void LCD_SendData(uint8_t data);

/*
 ================Функция передачи команды=========
 */
void LCD_SendCommand(uint8_t com);

/*
 =====================Функция инициализации дисплея==============
 */
void LCD_Init(void);
/*
 =====================Функция печати символа=========
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
/*
==========Функция записи пользовательского символа========================
*/
void InitCustomeChars(void);





#endif	/* LCD_H */

