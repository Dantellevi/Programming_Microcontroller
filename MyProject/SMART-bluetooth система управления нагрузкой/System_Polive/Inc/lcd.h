
#ifndef LCD_H
#define LCD_H
 //-----------------------------
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
//-------------------------------


//------------------------------------------
void LCD_ini(void);
//------------------------------------------
void LCD_clear(void);
//------------------------------------------
void LCD_printchar(char ch);
//------------------------------------------
void LCD_printstring(char* str);
//------------------------------------------
void LCD_GOTOXY(uint8_t x, uint8_t y);
//------------------------------------------
//------------------------------------------
void LCD_PrintStringXY(char* str,uint8_t x , uint8_t y);




#endif /* LCD_H */


