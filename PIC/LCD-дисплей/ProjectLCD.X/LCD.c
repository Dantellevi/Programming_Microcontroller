#include "LCD.h"

extern const unsigned short MyChar5x8[];

/*
 ===================Функция передачи данных ===========
 */
void LCD_SendData(uint8_t data)
{
    if(data&0x01)
	{
		D4_set;
		
	}
	else
	{
		D4_reset;
	}
	
	if(data&0x02)
	{
		D5_set;
		
	}
	else
	{
		D5_reset;
	}
	
	if(data&0x04)
	{
		D6_set;
		
	}
	else
	{
		D6_reset;
	}
	
	if(data&0x08)
	{
		D7_set;
		
	}
	else
	{
		D7_reset;
	}
}




/*
 ================Функция передачи команды=========
 */
void LCD_SendCommand(uint8_t com)
{
    RS_COM();//указываем что передаем команду
    LCD_SendData(com);
    E_SET();    //стробирование
    E_RESET();
    __delay_ms(4);
}


/*
 =====================Функция инициализации дисплея==============
 */
void LCD_Init(void)
{
    DDR_D4=0;
    DDR_D5=0;
    DDR_D6=0;
    DDR_D7=0;
    
    DDR_RS=0;
    DDR_RW=0;
    DDR_E=0;
    
    __delay_ms(20);
    LCD_SendCommand(0x03);
    __delay_ms(40);
    LCD_SendCommand(0x03);
     __delay_ms(40);
    LCD_SendCommand(0x03);
    __delay_ms(40);
    LCD_SendCommand(0x02);
    __delay_ms(40);
    LCD_SendCommand(0x02);
    LCD_SendCommand(OFF_DISPLAY);
    LCD_SendCommand(0x00);
    LCD_SendCommand(OFF_DISPLAY);
    LCD_SendCommand(0x00);
    LCD_SendCommand(CLEAR_DISPLAY);
    LCD_SendCommand(0x00);
    LCD_SendCommand(Shift_Cursor_R);
    LCD_SendCommand(0x00);
    LCD_SendCommand(ON_Display);
    
}



/*
 =====================Функция печати символа=========
 */
void Lcd_Print_char(char data)
{
    RS_DATA();
    LCD_SendData(data>>4);//передаем старшие 4 бита
	E_SET();
	E_RESET();
	LCD_SendData(data&0x0F);//передаем младшие 4 бита
	E_SET();
	E_RESET();
	__delay_ms(4);
}


/*
====================Функция печати строки========================
*/
void Lcd_PrintString(char *str)
{
	while ((*str)!='\0')
	{
		Lcd_Print_char(*str);
		str++;
	}
}


/*
=======================Функция очистки дисплея=========================
*/
void Lcd_Clear(void)
{
	LCD_SendCommand(0x00);
	LCD_SendCommand(CLEAR_DISPLAY);

}

/*
================================Функция перехода по строкам и столбцами=====================
*/
void lcd_gotoxy(char x, char y)
{
	if(x > 39) x = 39;
	if(x < 0) x = 0;
	if(y > 3) y = 3;
	if(y < 0) y = 0;
	
	char temp = 0x00;

	RS_COM();
	
	switch (y)
	{
		case 0:
		{
			temp |= (0x80 + x);
			LCD_SendCommand(temp >> 4);			
			LCD_SendCommand(temp & 0x0F);		
			break;
		}
		case 1:
		{
			temp |= (0xC0 + x);
			LCD_SendCommand(temp >> 4);			
			LCD_SendCommand(temp & 0x0F);		
			break;
		}
		case 2:
		{
			temp |= (0x94 + x);
			LCD_SendCommand(temp >> 4);			
			LCD_SendCommand(temp & 0x0F);		
			break;
		}
		case 3:
		{
			temp |= (0xD4 + x);
			LCD_SendCommand(temp >> 4);			
			LCD_SendCommand(temp & 0x0F);		
			break;
		}
	}

}

/*
===============================Функция печати строки по координатам==========================
*/
void LCD_printStringXY(char *str,uint8_t x,uint8_t y)
{
	lcd_gotoxy(x,y);
	Lcd_PrintString(str);
}


/*
==========Функция записи пользовательского символа========================
*/
void InitCustomeChars(void)
{
	char i;
	LCD_SendCommand(0x04);	//устанавливаем CGRAM Adress
	LCD_SendCommand(0x00);	//устанавливаем CGRAM Adress
	for(i=0;i<=63;i++)
	{
		Lcd_Print_char((char)MyChar5x8[i]);
	}
	LCD_SendCommand(0);
	LCD_SendCommand(2);

}








