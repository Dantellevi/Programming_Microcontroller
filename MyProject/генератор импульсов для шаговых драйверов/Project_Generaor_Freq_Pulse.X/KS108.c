#include "KS108.h"
#include "chars.h"



/*
======================Функция передачи команды на дисплей===============
			Принимаемые данные :
				unsigned char -значение команды для передачи
*/
void GLDKS108_SendCommand(unsigned char command)
{
    GLD_PORT=command;
    __delay_us(1);
    E_SET;
    __delay_us(1);
    E_RESET;
    __delay_us(1);
    
    
}


/*
============Функция передачи данных в контроллер дисплея==============
			Принимаемые параметры:
				unsigned char- данные для передачи
*/
void GLDKS108_SendData(unsigned char data)
{
    GLD_PORT=data;
    DI_SET;
    __delay_us(1);
    E_SET;
    __delay_us(1);
    E_RESET;
    DI_RESET;
    
}


//=======================================Функция очистки дисплея===================
void GLDKS108_Clear(void)
{
    if(CS==0)
    {
        CS1_RESET;
        CS2_RESET;
        
    }
    else
    {
        CS1_SET;
        CS2_SET;
    }
    
    for(unsigned char i=0;i<8;i++)
    {
        GLDKS108_SendCommand(0xB8+i);
        for (unsigned char j=0;j<64;j++)//Y
		{
			GLDKS108_SendCommand(0x40+j);
			if (MODE==0)
			{
				GLDKS108_SendCommand(0x00);

			}
			else
			{
				GLDKS108_SendCommand(0xFF);
			}
				
		}
    }
    
    if(CS==0)
    {
        CS1_SET;
        CS2_SET;
    }
    else
    {
        CS1_RESET;
        CS2_RESET;
    }
}





/*
===============================Функция перехода на строку и столбец==============
			Принимаемые параметры:
			unsigned char-координата х
			unsigned char-координата y
*/
void GLDKS108_GotoXY(unsigned char x, unsigned char y)
{
    if(y<64)
    {
        if(CS==0)
        {
            CS1_RESET;
            CS2_SET;
        }
        else
        {
            CS1_SET;
            CS2_RESET;
        }
        
    }
    else
    {
       if(CS==0)
        {
            CS1_SET;
            CS2_RESET;
        }
        else
        {
            CS1_RESET;
            CS2_SET;
        } 
       y=y-64;
    }
    
    
    GLDKS108_SendCommand(0xB8+x);
    GLDKS108_SendCommand(0x40+y);
    
}



/*
=============================Инициализация дисплея==============================
*/
void GLDKS108_Init(void)
{
    GLD_TRIS=0x00;
    TRIS_DI=0;
    TRIS_RW=0;
    TRIS_E=0;
    TRIS_CS1=0;
    TRIS_CS2=0;
    TRIS_RST=0;
    if(CS==0)
    {
        RST_SET;
    }
    else
    {
       RST_SET;
       CS1_SET;
       CS2_SET;
    }
    
    __delay_us(1000);
    //Вкл. дисплей
    GLDKS108_SendCommand(0x3F);
    //Y=0
	GLDKS108_SendCommand(0x40);
	//X=0
	GLDKS108_SendCommand(0xB8);
	GLDKS108_SendCommand(0xC0);
    
}

/*
==================================Функция отрисовки точки==============================
				Принимаемые параметры:
				unsigned char-координата х
				unsigned char-координата y
				
*/
void GLD_Draw_Point(unsigned char x, unsigned char y)
{
    RST_SET;
    __delay_us(100);
    unsigned char pins=0;
	if((x>63)||(y>127)) return;
    
    GLDKS108_GotoXY(x/8,y);
    GLD_PORT=0xFF;
    GLD_TRIS=0xFF;
    RW_SET;
    DI_SET;
    __delay_us(1);
    E_SET;
    __delay_us(1);
    E_RESET;
    __delay_us(1);
    E_SET;
    __delay_us(1);
    pins=GLD_PORT;
    E_RESET;
    
    
    if(MODE==0)
	pins |= (1<<(x%8));//
	else
	pins &= ~(1<<(x%8));
    RW_RESET;
    DI_RESET;
    GLD_TRIS=0x00;
    GLDKS108_GotoXY(x/8,y);
    GLDKS108_SendData(pins);
    RST_SET;
    __delay_us(100);
    
            
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
==========================================Функция отрисовки линии=========================
				Принимаемые значения:
				x1,y1- координаты первой точки линии
				x2,y2-координаты второй точки линии
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

/*
========================Функция вывода круга===========
	unsigned char x0-координата х цента,
 *  unsigned char y0-координата у цента, 
 * unsigned char radius- радиус круга
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
=================================Функция вывода символа на дисплей================
			Принимаемые параметры:
				x0,y0-координаты
				code-коде символа
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
        RST_SET;
        CS1_SET;
        CS2_RESET;
    }
    else
    {
        RST_SET;
        CS1_SET;
        CS2_RESET;
        
    }
    if(x>63 || y>127) return;
    for (unsigned char i=0;i<5;i++)
	{
		GLDKS108_GotoXY(x,y);
		if (i<=4)
		{
			if (MODE==0) 
			{
				GLDKS108_SendData(symbol[code][i]);
			}
			else
			{
				GLDKS108_SendData(~symbol[code][i]);
			}
		}
		y+=1;
	}
    
}



/*
 * ==========================Функция вывода строки==========
 * unsigned char x0-координата х для вывода строки,
 * unsigned char y0-координата у для вывода строки,
 * char* buffer- строка символов для вывода на дисплей, 
 * unsigned char count- размер строки
 */
void GLD_print_string(unsigned char x0,unsigned char y0,char* buffer, unsigned char count)
{
	unsigned char x=x0;
	unsigned char y=y0;
	if((x>8)||(y>127)) return;
	GLDKS108_GotoXY(x,y);
	for (unsigned char i=0;i<count;i++)
	{
		GLD_printChar(x,y+6*i,buffer[i]);
	}

}












