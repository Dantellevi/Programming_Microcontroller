#include "GLD.h"
#include "Fonts.h"



void KS108_SendCommand(uint8_t command)
{
	LCD_PORT=command;
	_delay_us(1);
	E_SET;
	_delay_us(1);
	E_RESET;
	_delay_us(1);
}




void KS108_SendData(uint8_t data)
{
	LCD_PORT=data;
	RS_SET;
	_delay_us(1);
	E_SET;
	_delay_us(1);
	E_RESET;
	RS_RESET;
}



/*
==========================Функция очистки экрана==================
*/
void KS108_Clear(void)
{
	if (CS==0)
	{
		CS1_RESET;
		CS2_RESSET;
	}
	else
	{
		CS1_SET;
		CS2_SET;
	}

	for (uint8_t i=0;i<8;i++)
	{
		KS108_SendCommand(0xB8+i);
		for (uint8_t j=0;j<64;j++)
		{
			KS108_SendCommand(0x40+j);
			if (MODE==0)
			{
				KS108_SendData(0x00);
			}
			else
			{
				KS108_SendData(0xFF);
			}
		}
	}

	if (CS==0)
	{
		CS1_SET;
		CS2_SET;
	}
	else
	{
		CS1_SET;
		CS2_SET;
	}
}


/*
====================================Функция перехода по координатам================
*/
void KS108_GoToXY(uint8_t x, uint8_t y)
{
	if(y<64)
	{
		if(CS==0)
		{
			CMD_PORT &= ~(1<<CS1);
			CMD_PORT |= (1<<CS2);
		}
		else
		{
			CMD_PORT |= (1<<CS1);
			CMD_PORT &= ~(1<<CS2);
		}
	}
	else
	{
		if(CS==0)
		{
			CMD_PORT &= ~(1<<CS2);
			CMD_PORT |= 1<<CS1;
		}
		else
		{
			CMD_PORT |= 1<<CS2;
			CMD_PORT &= ~(1<<CS1);
		}
		y=y-64;
	}
	KS108_SendCommand(0xB8+x);
	KS108_SendCommand(0x40+y);
}



/*
===================================Инициализация дисплея=============================
*/
void KS108_Init(void)
{
	LCD_DDR=0xFF;
	CMD_DDR |= (1<<DI)|(1<<RW)|(1<<E)|(1<<CS1)|(1<<CS2)|(1<<RST);
	if(CS==0)
	CMD_PORT |= (1<<RST);
	else
	CMD_PORT |=(1<<RST)|(1<<CS1)|(1<<CS2);

	_delay_us(100);
	//Вкл дисплей
	KS108_SendCommand(0x3F);
	//Y=0
	KS108_SendCommand(0x40);
	//X=0
	KS108_SendCommand(0xB8);
	KS108_SendCommand(0xC0);
}



/*
====================================Функция отрисовки пикселя========================
*/
void GLD_Draw_Point(uint8_t x, uint8_t y)
{
	CMD_PORT |= (1<<RST);
	_delay_us(100);
	unsigned char pins=0;
	if((x>63)||(y>127)) return;

	KS108_GoToXY(x/8,y);
	LCD_PORT=0xFF;
	LCD_DDR=0x00;
	CMD_PORT |= (1<<RW)|(1<<DI);
	_delay_us(1);
	CMD_PORT |= (1<<E);
	_delay_us(1);
	CMD_PORT &= ~(1<<E);
	_delay_us(1);
	CMD_PORT |= (1<<E);
	_delay_us(1);//в реальном устройстве здесь нужно поставить 10мкс, а в Протеусе - 1мкс
	pins=LCD_PIN;
	CMD_PORT &= ~(1<<E);

	if(MODE==0)
	pins |= (1<<(x%8));//
	else
	pins &= ~(1<<(x%8));
	CMD_PORT &= ~((1<<RW)|(1<<DI));
	LCD_DDR = 0xFF;

	KS108_GoToXY(x/8,y);
	KS108_SendData(pins);
	CMD_PORT |= (1<<RST);
	_delay_us(100);
}


/*
====================Функция определения абсолютного значения переменной===============
			Принимаемые значения:
					int-значения для проверки
			Возращаемое значения:
					int- абсолютное значение

*/
int GLD_abs(int x)
{
	if(x<0) return -x;
	else return x;
}

int GLD_sign(int x)
{
	if(x<0) return -1;
	if(x>0) return 1;
	else return 0;
}


/*
=====================================Функция отрисовки линии===========================
*/
void GLD_Draw_Line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
{
	int dX = GLD_abs(x2 - x1);
	int dY = GLD_abs(y2 - y1);
	int signX = GLD_sign(x2-x1);
	int signY = GLD_sign(y2-y1);
	int err = dX - dY;
	int err2;
	while(1)
	{
		GLD_Draw_Point(x1, y1);
		if(x1 == x2 && y1 == y2) break;
		err2 = err * 2;
		if(err2 > -dY)
		{
			err -= dY;
			x1 += signX;
		}
		if(err2 < dX)
		{
			err += dX;
			y1 += signY;
		}
	}
}


/*
========================Функция вывода прямоугольника без заливки===========
	x1,y1-координаты нижней левой точки прямоугольник
	x2,y2-координаты верхней правой точки прямоугольника

*/

void GLD_Draw_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)
{
	GLD_Draw_Line(x1,y1,x1,y2);
	GLD_Draw_Line(x1,y2,x2,y2);
	GLD_Draw_Line(x2,y2,x2,y1);
	GLD_Draw_Line(x2,y1,x1,y1);

}




//===========================================================================


/*
========================================Функция отрисовки окружности=====================
*/
void GLD_Draw_Ellipse(unsigned char x0, unsigned char y0, unsigned char radius)
{
	int x = 0;
	int y = radius;
	int delta = 2 - 2 * radius;
	int error = 0;
	while(y >= 0)
	{
		GLD_Draw_Point(x0 + x, y0 + y);
		GLD_Draw_Point(x0 + x, y0 - y);
		GLD_Draw_Point(x0 - x, y0 + y);
		GLD_Draw_Point(x0 - x, y0 - y);
		error = 2 * (delta + y) - 1;
		if(delta < 0 && error <= 0)
		{
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if(delta > 0 && error > 0)
		{
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}


/*
==========================Функция прорысовки символа===============
*/
void GLD_printChar(unsigned char x0,unsigned char y0,unsigned char code)
{
	unsigned char x=x0;//0..8 - задаем строку где буква выводится
	unsigned char y=y0;
	if(code<0x80)
	code-=0x20;//установка начала стандартных символов
	else
	code-=0x60;//установка начала русских символов
	if(CS==0)
	{
		CMD_PORT |= (1<<RST)|(1<<CS1);
		CMD_PORT &= ~(1<<CS2);
	}
	else
	{
		CMD_PORT |= (1<<RST)|(1<<CS1);
		CMD_PORT &= ~(1<<CS2);
	}
	if(x>63 || y>127) return;

	for (unsigned char i=0;i<5;i++)
	{
		KS108_GoToXY(x,y);
		if (i<=4)
		{
			if (MODE==0)
			{
				KS108_SendData(symbol[code][i]);
			}
			else
			{
				KS108_SendData(~symbol[code][i]);
			}
		}
		y+=1;
	}

}


/*
=======================================Функция прорысовки строки =========================
*/
void GLD_print_string(unsigned char x0,unsigned char y0,char* buffer, unsigned char count)
{
	unsigned char x=x0;
	unsigned char y=y0;
	if((x>8)||(y>127)) return;
	KS108_GoToXY(x,y);
	for (unsigned char i=0;i<count;i++)
	{
		GLD_printChar(x,y+6*i,buffer[i]);
	}

}


/*
=================================Функция динамического вывода строки====================
*/
void GLD_Printf_String(uint8_t x, uint8_t y, char *str)
{
	GLD_print_string(x,y,str,strlen(str));
}

