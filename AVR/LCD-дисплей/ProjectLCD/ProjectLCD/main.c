#include "Main.h"


int main(void)
{
   LCD_Init();
   Lcd_Clear();
   lcd_gotoxy(0,0);
   Lcd_PrintString("Hello World!!!");

    while (1) 
    {
    }
}

