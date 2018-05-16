#include "LCD.h"


/*
 ============================Функция передачи данных на дисплей=============
 * Принимаемые параметры:
 * data- данные для выставления в дисплей
 */
void Send_Data(char data)
{
    if(data&0x01)
    {
        D4=1;
        
    }
    else
    {
        D4=0;
    }
    
    if(data&0x02)
    {
        D5=1;
        
    }
    else
    {
        D5=0;
    }
    
    if(data&0x04)
    {
        D6=1;
        
    }
    else
    {
        D6=0;
    }
    
    if(data&0x08)
    {
        D7=1;
        
    }
    else
    {
        D7=0;
    }
}

/*
 ========================Функция передачи команды ======================
 * Принимаемые параметры:
 * com-команда для передачи
 */
void Send_command(char com)
{
	RS_COM();			//передаем данные	
	Send_Data(com);		//выставляем в порт	
	E_SET();			//разрешение ON 	
	E_RESET();			//разрешение OFF	
	__delay_ms(4);		//задержка	
}


/*
 ==================================Функция Инициализации дислпея===========
 */
void lcd_init(char lcd)
{
	DDR_COMAND=0x00;
    DDR_DATA=0x00;
    
	switch (lcd)
	{
		case 0: lcd = 0x0C; break;
		case 1: lcd = 0x0D; break;
		case 2: lcd = 0x0E; break;
		case 3: lcd = 0x0F; break;
	}

	__delay_ms(20);		
	
	Send_command(0x03);		
	__delay_us(40);
	Send_command(0x03);		
	__delay_us(40);
	Send_command(0x03);		
	__delay_us(40);
	Send_command(0x02);		
	__delay_us(40);
	Send_command(0x02);		
	Send_command(0x08);		
	Send_command(0x00);		
	Send_command(0x08);		
	Send_command(0x00);		
	Send_command(0x01);		
	Send_command(0x00);		
	Send_command(0x06);		
	Send_command(0x00);		
	Send_command(lcd);		
}


/*
 ============================Функция вывода одного символа========================
 */
void lcd_Print_char(char data)
{
	RS_DATA();							
	Send_Data(data >> 4);					
	E_SET();
	E_RESET();
	Send_Data(data & 0x0F);				
	E_SET();
	E_RESET();
	__delay_ms(4);						
}



/*
 ==========================Функция вывода строки символов======================
 */
void lcd_printString(char *str)
{
	while((*str) != '\0')
	{
		lcd_Print_char(*str);
		str++;
	}
}

/*
 ========================Функция перехода по определенным строками и столбцам===========
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
			Send_command(temp >> 4);			// ???????? ??????? 4 ???
			Send_command(temp & 0x0F);		// ???????? ??????? 4 ???
			break;
		}
		case 1:
		{
			temp |= (0xC0 + x);
			Send_command(temp >> 4);			// ???????? ??????? 4 ???
			Send_command(temp & 0x0F);		// ???????? ??????? 4 ???
			break;
		}
		case 2:
		{
			temp |= (0x94 + x);
			Send_command(temp >> 4);			// ???????? ??????? 4 ???
			Send_command(temp & 0x0F);		// ???????? ??????? 4 ???
			break;
		}
		case 3:
		{
			temp |= (0xD4 + x);
			Send_command(temp >> 4);			// ???????? ??????? 4 ???
			Send_command(temp & 0x0F);		// ???????? ??????? 4 ???
			break;
		}
	}

}




/*
 =======================Функция вывода строки по координатам===================
 */
void lcd_printStringXY(char *str,char x,char y)
{
	lcd_gotoxy(x,y);
	lcd_printString(str);
}



/*
 ==================================Функция очистки дисплея======================
 */
void lcd_clear(void)
{
	Send_command(0x00);
	Send_command(0x01);
}




