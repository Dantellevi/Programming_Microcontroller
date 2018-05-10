
#include "Main.h"

const unsigned short MyChar5x8[] = {
	0x07, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x00, // Code for char num #0
	0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00, // Code for char num #1
	0x0E, 0x1B, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x00, // Code for char num #2
	0x0E, 0x1B, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x00, // Code for char num #3
	0x0E, 0x1B, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, // Code for char num #4
	0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, // Code for char num #5
	0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00, 0x00, // Code for char num #6
	0x00, 0x00, 0x0E, 0x11, 0x11, 0x0A, 0x1B, 0x00  // Code for char num #7
};

void main(void)
{
     LCD_Init();
     Lcd_Clear();
//    lcd_gotoxy(0,0);
//    Lcd_PrintString("Hello World!!!");
	InitCustomeChars();
    while(1)
    {
        Lcd_Clear();
	lcd_gotoxy(1,1);
	Lcd_Print_char(0);
	Lcd_Print_char(1);
	Lcd_Print_char(2);
	Lcd_Print_char(3);
	Lcd_Print_char(4);
	Lcd_Print_char(5);
	Lcd_Print_char(6);
	Lcd_Print_char(7);
	LCD_printStringXY("Hello",2,2);
	__delay_ms(1000);
    }
}
