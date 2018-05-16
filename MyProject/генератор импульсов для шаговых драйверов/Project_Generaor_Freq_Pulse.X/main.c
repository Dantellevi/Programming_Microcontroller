#include <pic16f877a.h>

#include "Main.h"

#define DIR_LEFT 1
#define DIR_RIGHT 2


#define DIR_L  RA4
#define DIR_R  RA5


uint8_t flag_count=1;
uint8_t flag_Work=0;
const char data[3][40]=
{
  "Genearate ON \0",
  "Genearate OFF\0",
  "Freq: ---- Hz\0"
};

char dataFreq[40];

void Port_Init(void)
{
    //================================вход кнопки вкл. генерации===============
    TRISC5=1;
    PORTCbits.RC5=0;
    //============================выход разрешения работы и направления вращения==================================
    TRISC6=0;
    TRISB7=0;
    PORTCbits.RC6=0;
    PORTBbits.RB7=0;
    //=====================================Индикация =====================================================
    TRISC3=0;
    TRISC4=0;
    PORTCbits.RC3=0;
    PORTCbits.RC4=0;
    
    //=============================Индикация======================
    TRISE0=0;
    TRISE1=0;
    TRISE2=0;
    PORTEbits.RE0=0;
    PORTEbits.RE1=0;
    PORTEbits.RE2=0;
    //============================Вход кнопок вкл. разрешения и направления вращения двигателя=================================
    
    TRISA4=0;
    TRISA5=0;
    
    
    PORTAbits.RA4=0;
    PORTAbits.RA5=0;
}

/*
 =====================Функция установки разрешающего флага==============================
 */
void ENABLE_SET(void)
{
    PORTCbits.RC6=1;
    PORTEbits.RE0=1;
}


/*
 ========================Функция отключения разрешения==================================
 */
void ENABLE_RESET(void)
{
    PORTCbits.RC6=0;
    PORTEbits.RE0=0;
}

/*
 =========================Функция разрешения вращения=====================================
 */
void DIRECTION_SET(uint8_t dir)
{
    switch(dir)
    {
        case DIR_LEFT:
        {
            PORTBbits.RB7=0;
            PORTEbits.RE1=1;
            PORTEbits.RE2=0;
            break;
        }
        
        case DIR_RIGHT:
        {
            PORTBbits.RB7=1;
            PORTEbits.RE1=0;
            PORTEbits.RE2=1;
            break;
        }
    }
}

/*
 ===========================Функция опроса входов МК=========================
 
 * 
 * Возращаемые значения:
 * 1-кнопка нажата
 * 0-кнопка не нажата
 */
uint8_t check_button(void)
{
    uint8_t result=0;
    uint16_t butcount=0;
    
    while(RC5)
    {
        			
        if(butcount<DELAY)
		{
            butcount++;
		}
		else
		{
			result=1;
			break;
		}
    }
    
    return result;
}

/*
 ===========================Функция опроса входов МК=========================
 * Принимаемые параметры:
 * flag-номер пина
 
 * 
 * Возращаемые значения:
 * 1-кнопка нажата
 * 0-кнопка не нажата
 */
uint8_t check_buttonSelect(uint8_t flag)
{
    uint8_t result=0;
    uint16_t butcount=0;
    
    
    while(flag)
    {
        			
        if(butcount<DELAY)
		{
            butcount++;
		}
		else
		{
			result=1;
			break;
		}
    }
    
   
    return result;
}

void main(void) 
{
    uint16_t Frequnsy;
   
    Port_Init();
    Timer1_init();
    ADC_Init(5);
    lcd_init(0);
    char testbuf[40];
         
    while(1)
    {
           
        
       //GLD_print_string(1,15,(char*)data[0],sizeof(data[0])-1);
         if(check_button()==1)
        {
            flag_count++;
        }
        
        if(flag_count%2==0)
        {
            PORTCbits.RC3=1;
            PORTCbits.RC4=0;
            
            //------------Вкл. разрешение работы----------
            lcd_printStringXY("ENABLE ON ",2,1);
            ENABLE_SET();
            
            //----------------Проверяем направления вращения----------------
            
            
            if(check_buttonSelect(DIR_R)==1)
            {
                flag_Work=1;
                
            }
            if(check_buttonSelect(DIR_L)==1)
            {
              flag_Work=0;
              
            }
            
            switch( flag_Work)
            {
                case 0:
                {
                    DIRECTION_SET(DIR_LEFT);
                   
                    lcd_printStringXY("DIR LEFT ",3,3);
                    
                    break;
                }
                case 1:
                {
                    DIRECTION_SET(DIR_RIGHT);
                    
                   lcd_printStringXY("DIR RIGHT",3,3);
                    break;
                }
            }
           
                       
            //-----------------------------------------------
            //выводим старт генерации импульсов
            lcd_printStringXY(data[0],4,0);
            //стартуем генератор 
            Start_Timer();
            //считываем показания с АЦП и преобразуем ее в частоту
            Frequnsy=ReadValue();
            //выводим значение частоты на дисплей- Частота: 1000 Гц
            sprintf(dataFreq,"Freq: %d%d%d%d Hz ",Frequnsy/1000,(Frequnsy%1000)/100,(Frequnsy%100)/10,Frequnsy%10);
            lcd_printStringXY(dataFreq,2,2);
            
        }
        else if(flag_count%2!=0)
        {
            PORTCbits.RC3=0;
            PORTCbits.RC4=1;
            lcd_printStringXY("ENABLE OFF",2,1);
            ENABLE_RESET();
            //выводим на дисплей остановка генерации
            lcd_printStringXY(data[1],4,0);
            //останавливаем генератор
            Stop_Timer();
            //выводим  в полях частоты ---- Гц
           lcd_printStringXY(data[2],2,2);
            
        }
        
    
    }
        /*
         
         
       
         * */
}












