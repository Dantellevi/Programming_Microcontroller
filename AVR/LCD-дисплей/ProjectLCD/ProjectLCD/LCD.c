#include "LCD.h"

/*
=======================Функция передачи данных в контроллер======================
*/
void LCD_SendData(uint8_t data)
{
	if(data&0x01)
	{
		PORT_DATA|=(1<<D4);
		
	}
	else
	{
		PORT_DATA&=~(1<<D4);
	}
	
	if(data&0x02)
	{
		PORT_DATA|=(1<<D5);
		
	}
	else
	{
		PORT_DATA&=~(1<<D5);
	}
	
	if(data&0x04)
	{
		PORT_DATA|=(1<<D6);
		
	}
	else
	{
		PORT_DATA&=~(1<<D6);
	}
	
	if(data&0x08)
	{
		PORT_DATA|=(1<<D7);
		
	}
	else
	{
		PORT_DATA&=~(1<<D7);
	}
}



/*
=============================Функция передачи команды=============================
*/
void LCD_SendCommand(uint8_t com)
{
	RS_COM();		//опускаем в нолль передаем команду
	LCD_SendData(com);	//передаем данные
	E_SET();	//стробирование
	E_RESET();
	_delay_ms(4);//задерка для установления значения
}


/*
======================Функция инициализации дисплея==============
*/
void LCD_Init(void)
{
	DDR_DATA|=(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);
	DDR_COMMAND|=(1<<RS)|(1<<RW)|(1<<E);

	_delay_ms(20);
	LCD_SendCommand(0x03);	
	_delay_us(40);
	LCD_SendCommand(0x03);
	_delay_us(40);
	LCD_SendCommand(0x03);
	_delay_us(40);
	LCD_SendCommand(0x02);
	_delay_us(40);
	LCD_SendCommand(0x02);
	LCD_SendCommand(0x08);// полное выключение дисплея
	LCD_SendCommand(0x00);
	LCD_SendCommand(0x08);// полное выключение дисплея
	LCD_SendCommand(0x00);
	LCD_SendCommand(0x01); // очистка дисплея
	LCD_SendCommand(0x00);
	LCD_SendCommand(0x06);// сдвиг курсора вправо
	LCD_SendCommand(0x00);
	LCD_SendCommand(0x0C);// включение дисплея
}



/*
===========================Функция вывода символа======================
*/
void Lcd_Print_char(char data)
{
	RS_DATA();//передаем данные
	LCD_SendData(data>>4);//передаем старшие 4 бита
	E_SET();
	E_RESET();
	LCD_SendData(data&0x0F);//передаем младшие 4 бита
	E_SET();
	E_RESET();
	_delay_ms(4);

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
	LCD_SendCommand(0x01);

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
			LCD_SendCommand(temp >> 4);			// ???????? ??????? 4 ???
			LCD_SendCommand(temp & 0x0F);		// ???????? ??????? 4 ???
			break;
		}
		case 1:
		{
			temp |= (0xC0 + x);
			LCD_SendCommand(temp >> 4);			// ???????? ??????? 4 ???
			LCD_SendCommand(temp & 0x0F);		// ???????? ??????? 4 ???
			break;
		}
		case 2:
		{
			temp |= (0x94 + x);
			LCD_SendCommand(temp >> 4);			// ???????? ??????? 4 ???
			LCD_SendCommand(temp & 0x0F);		// ???????? ??????? 4 ???
			break;
		}
		case 3:
		{
			temp |= (0xD4 + x);
			LCD_SendCommand(temp >> 4);			// ???????? ??????? 4 ???
			LCD_SendCommand(temp & 0x0F);		// ???????? ??????? 4 ???
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




