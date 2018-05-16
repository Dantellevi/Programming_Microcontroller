#include "LCDlib.h"


/*
 ===================Функция отправки данных======
 * data- данные для передачи
 */
void LCD_SendData(uint8_t data)
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
 =================Функция передачи команды========
 * com- команда для передачи
 */
void LCD_SendCommand(uint8_t com)
{
    RS_COM();//записываем команду
    LCD_SendData(com);//выставляем команду
    E_SET();//производим стробирование
    E_RESET();
    __delay_ms(4);
}



/*
 ==========================Функция инициализации===========
 */
void LCD_Init(char lcd)
{
    DDR_RS=0;
    DDR_RW=0;
    DDR_E=0;
    DDR_DATA=0x00;
    
	switch (lcd)
	{
		case 0: lcd = 0x0C; break;
		case 1: lcd = 0x0D; break;
		case 2: lcd = 0x0E; break;
		case 3: lcd = 0x0F; break;
	}
    
    __delay_ms(20);
    LCD_SendCommand(0x03);
    __delay_us(40);
    LCD_SendCommand(0x03);
    __delay_us(40);
    LCD_SendCommand(0x03);
    __delay_us(40);
    LCD_SendCommand(0x02);
    __delay_us(40);
    LCD_SendCommand(0x02);
    LCD_SendCommand(0x08);
    LCD_SendCommand(0x00);
    LCD_SendCommand(0x08);
    LCD_SendCommand(0x00);
    LCD_SendCommand(0x01);
    LCD_SendCommand(0x00);
    LCD_SendCommand(0x06);
    LCD_SendCommand(0x00);
    LCD_SendCommand(lcd);
}


/*
 ==========================Функция вывода символа на дисплей==============
 */
void LCD_PrintChar(char c)
{
    RS_DATA();
    LCD_SendData(c>>4);
    E_SET();
    E_RESET();
    LCD_SendData(c&0x0F);
    E_SET();
    E_RESET();
    __delay_ms(4);
    
     
}


/*
 ==================Функция вывода строки символов========
 */
void LCD_PrintString(char *str)
{
    while((*str)!='\0')
    {
        LCD_PrintChar(*str);
        str++;
    }
}

/*
 ================Функция перехода по строкам =======
 */
void LCD_GoToXY(uint8_t x,uint8_t y)
{
    if(x > 39) x = 39;
	if(x < 0) x = 0;
	if(y > 3) y = 3;
	if(y < 0) y = 0;
    char temp = 0x00;
    RS_COM();
    
    switch(y)
    {
        case 0:
        {
            temp|=(0x80+x);
            LCD_SendCommand(temp>>4);
            LCD_SendCommand(temp&0x0F);
            break;
        }
        case 1:
        {
            temp|=(0xC0+x);
            LCD_SendCommand(temp>>4);
            LCD_SendCommand(temp&0x0F);
            break;
        }
        case 2:
        {
            temp|=(0x94+x);
            LCD_SendCommand(temp>>4);
            LCD_SendCommand(temp&0x0F);
            break;
        }
        
        case 3:
        {
            temp|=(0xD4+x);
            LCD_SendCommand(temp>>4);
            LCD_SendCommand(temp&0x0F);
            break;
        }
    }
    
}

/*
 ===========Функция печати строки по координатам========
 */
void LCD_PrintStringXY(char *str,char x,char y)
{
    LCD_GoToXY(x,y);
    LCD_PrintString(str);
}



/*
 ==================Функция очистки дисплея===========
 */
void LCD_Clear(void)
{
    LCD_SendCommand(0x00);
    LCD_SendCommand(0x01);
}






