/*
 * project_RGB.c
 *
 * Created: 06.12.2016 12:06:11
 * Author : DANTE_L_LEVI
 */ 


#include "Main.h"




 unsigned int flag_work=0;//флаг установки режима работы
 unsigned int color=1;//флаг установки цвета 


 int second=0;//секунды
 int minuts=0;//минуты
 int hose=0;//часы
 int day=0;//день недели
 int data=0;//дата
 int mesiac=0;//мес€ц
 int year=0;//год

 int R_rand=0;
 int G_rand=0;
 int B_rand=0;


void Port_init(void)//инициализаци€ портов ввода/вывода
{
DDRB|=(1<<PB3);
PORTB&=~(1<<PB3);


DDRD|=(1<<PD7)|(1<<PD5)|(1<<PD4);
PORTD&=~((1<<PD7)|(1<<PD5)|(1<<PD4));

DDRB&=~((1<<PB0)|(1<<PB1));
PORTB|=(1<<PB0)|(1<<PB1);



DDRC|=(1<<PC7);
DDRC|=(1<<PC4);
DDRC|=(1<<PC3);
DDRC|=(1<<PC2);

PORTC&=~(1<<PC7);
PORTC&=~(1<<PC4);
PORTC&=~(1<<PC3);
PORTC&=~(1<<PC2);



}


void Color_settings(unsigned char color)//выбор цвета в режиме работы 1
{

if (color==1)
{
//красный
uart_write("color red");
uart_putc(0x0d);
uart_putc(0x0a);
OCR0=254;
OCR1A=1;
OCR2=1;

_delay_ms(250);
}

if (color==2)
{
//оранжевый
uart_write("color orange");
uart_putc(0x0d);
uart_putc(0x0a);
OCR0=250;
OCR1A=54;
OCR2=1;
_delay_ms(250);
}

if (color==3)
{
//зеленый
uart_write("color green");
uart_putc(0x0d);
uart_putc(0x0a);
	OCR0=10;
	OCR1A=209;
	OCR2=10;
	_delay_ms(250);
}
if (color==4)
{
//синий
uart_write("color blue");
uart_putc(0x0d);
uart_putc(0x0a);
OCR0=8;
OCR1A=13;
OCR2=220;
_delay_ms(250);
}

if (color==5)
{
	
	uart_write("color fialot");
	uart_putc(0x0d);
	uart_putc(0x0a);
	OCR0=150;
	OCR1A=59;
	OCR2=168;
	_delay_ms(250);
}

if (color==6)
{
	
	uart_write("color 6");
	uart_putc(0x0d);
	uart_putc(0x0a);
	OCR0=255;
	OCR1A=234;
	OCR2=5;
	_delay_ms(250);
}
if (color>6)
{
OCR0=2+rand()%255;
OCR1A=2+rand()%250;
OCR2=2+rand()%255;
uart_write("RANDOM!");
uart_putc(0x0d);
uart_putc(0x0a);
_delay_ms(250);
}

}


void Timer_init(void)//инициализаци€ Ў»ћ(таймеров счетчиков )OCR2,OCR0,OCR1A
{
//Timer 0
TCCR0|=(1<<WGM00)|(1<<WGM01);
TCCR0|=(1<<COM01);

TCCR0|=(1<<CS01);



//end

//timer1 

TCCR1A|=(1<<COM1B1)|(0<<COM1B0)|(1<<WGM10)|(0<<WGM11)|(1<<COM1A1)|(0<<COM1A0);
TCCR1B|=(1<<WGM12)|(0<<WGM13)|(1<<CS11);



//end


//Timer 2

TCCR2|=(1<<WGM20)|(1<<WGM21);
TCCR2|=(1<<COM21);

TCCR2|=(1<<CS21);






}



void Clock(void)//работа микросхемы часов ds1307 и вывод данных в UART интерфейс
{


I2C_SendByADDR(0,0b11010000);
_delay_ms(300);
I2C_Start();

I2C_SendByte(0b11010001);//отправл€ем в устройство бит чтени€
second=I2C_ReadByte();
minuts=I2C_ReadByte();
hose=I2C_ReadByte();
day=I2C_ReadByte();
data=I2C_ReadByte();
mesiac=I2C_ReadByte();
year=I2C_ReadLastByte();
I2C_Stop();
second=RTC_ConvertDEC(second);
minuts=RTC_ConvertDEC(minuts);
hose=RTC_ConvertDEC(hose);
day=RTC_ConvertDEC(day);
data=RTC_ConvertDEC(data);
mesiac=RTC_ConvertDEC(mesiac);
year=RTC_ConvertDEC(year);
//---------------------------------------------------


uart_putc(0x0d);
uart_putc(0x0a);
uart_putc(data/10+0x30);//преобразуем число в код числа
uart_putc(data%10+0x30);//преобразуем число в код числа
uart_putc('.');
uart_putc(mesiac/10+0x30);//преобразуем число в код числа
uart_putc(mesiac%10+0x30);//преобразуем число в код числа
uart_putc('.');
uart_putc(year/10+0x30);//преобразуем число в код числа
uart_putc(year%10+0x30);//преобразуем число в код числа
uart_putc('.');
uart_putc('.');
uart_putc('.');
uart_putc('.');
uart_putc('.');
uart_putc(day+0x30);
uart_putc('.');
uart_putc('.');
uart_putc('.');
uart_putc(hose/10+0x30);//преобразуем число в код числа
uart_putc(hose%10+0x30);
uart_putc(':');
uart_putc(minuts/10+0x30);//преобразуем число в код числа
uart_putc(minuts%10+0x30);
uart_putc(':');
uart_putc(second/10+0x30);//преобразуем число в код числа
uart_putc(second%10+0x30);
uart_putc(0x0d);
uart_putc(0x0a);


}



int main(void)
{
 Port_init();
 Timer_init();
 sei();
uart_init(9600);
uart_write("hello");
uart_putc(0x0d);
uart_putc(0x0a);

  
  OCR0=5;OCR1A=5;OCR2=5;
  PORTC|=(1<<PC7);
   PORTC&=~(1<<PC2);
    while (1) 
    {
	
		if (!(PINB&(1<<PB0)))//кнопка выбора режима работы
		{
		_delay_ms(100);
		flag_work++;
			if (flag_work>4)
			{
			flag_work=0;
			}
		}

		if (!(PINB&(1<<PB1)))//кнопка выбора цвета
		{
			_delay_ms(100);
			color+=1;
			

		}

		
		if (flag_work==1)//первый режим работы посто€нно горит с выбором цвета
		{
		PORTC|=(1<<PC2);
		PORTC&=~(1<<PC3);
		PORTC&=~(1<<PC4);
		Color_settings(color);
		}




		if (flag_work==2)//второй режим работы с работой часов и включение определенного цвета в определенное врем€
		{
		PORTC&=~(1<<PC2);
		PORTC|=(1<<PC3);
		Clock();
		uart_write(" clock-0n!!");
		uart_putc(0x0d);
		uart_putc(0x0a);
		_delay_ms(250);
		if ((hose>=7)&&(hose<8))
		{

		OCR2=155;
		OCR0=100;
		OCR1A=10;

		uart_write("clock 7-8");
		uart_putc(0x0d);
		uart_putc(0x0a);
		_delay_ms(250);
		}
	 if((hose>=16)&&(hose<20))
		{
		OCR2=100;
		OCR0=254;
		OCR1A=200;

		uart_write("clock 17-20");
		uart_putc(0x0d);
		uart_putc(0x0a);
		_delay_ms(250);

		}
		else{
		R_rand=2+rand()%255;
		G_rand=2+rand()%250;
		B_rand=2+rand()%255;

		OCR2=B_rand;
		OCR0=G_rand;
		OCR1A=R_rand;
		
		uart_write("end brenth");

		_delay_ms(150);
		}
		}

		if(flag_work==3)//третий режим работы - ждущий режим
		{
			PORTC&=~(1<<PC2);
			PORTC&=~(1<<PC3);
			PORTC|=(1<<PC4);
			OCR0=0;OCR1A=0;OCR2=0;
			uart_write("work 3");
			uart_putc(0x0d);
			uart_putc(0x0a);

		}




		
    }
}

