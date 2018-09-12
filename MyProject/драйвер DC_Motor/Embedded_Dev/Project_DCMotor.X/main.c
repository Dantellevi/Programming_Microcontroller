#include "Main.h"
#include <stdlib.h>
int16_t Uz_pwm;
uint8_t Phs_n_pwm1;
uint8_t Phs_z_pwm1;
uint8_t Phs_p_pwm1;
#define COUNT_DELAY 5000
#define TMR2PRESCALE 4      //предделитель таймера
long int freq=2000;//значение частоты генерации ШИМ


/*--------------------Инициализация портов МК-----------------*/
void Port_Init(void);
/*--------------------Инициализация 16-битного таймера--------------*/
void Timer1_Init(void);
/*----------------Функция инициализации ШИМ для вентелятора------------------*/
void PWM_Init(void);
/*----------------------Функция установки значния ШИМ----------*/
void PWM_SetValue(uint16_t val);
/*-------------------Функция нажатия на кнопку направления движения двигателя----------------*/
uint8_t Check_button_direction(void);
/*-----------------Функция проверки режима работы устройства---------------------*/
uint8_t Check_ModeWork(void);


/*-----------------Прерывания по переполнению  таймера 1----------------*/
void interrupt Timer1_OVF_Vector(void)
{
    if(TMR1IE&&TMR1IF)
    {
        if(Phs_p_pwm1==2)
        {
            PORTD = 0x0B; //подаем «1» на IN1, SD1, SD2
            Phs_p_pwm1=3;
        }
        if(Phs_p_pwm1==4)
        {
            PORTD = 0x0B; //подаем «1» на IN1, SD1, SD2
            Phs_p_pwm1=1;
        }
        if(Phs_n_pwm1==2)
        {
            PORTD = 0x0E; //подаем «1» на IN2, SD1, SD2
            Phs_n_pwm1=3;
        }
        if(Phs_n_pwm1==4)
        {
            PORTD = 0x0E; //подаем «1» на IN2, SD1, SD2
            Phs_n_pwm1=1;
        }
    }
    TMR1IF=0; // сброс бита прерывания
}



void main(void) {
    
    GIE=1;      //вкл. глобальные прерывания
    PEIE=1;//разрешение прерываний переферии
    
    Port_Init();    //Инициализация портов
    Timer1_Init();  //Инициализация таймера
    PWM_Init();
    PWM_SetValue(900);
    Usart_Init(9600);
    ADC_Init(5.0);
    
    char buf[5];//буффер для приема скорости вращения
    uint16_t adcVal;//прием значения с АЦП
    int16_t ConvertSpeed;//переменная для хранения конвертированного значения
    
    while(1)
    {
        if(Check_ModeWork()==1)//USART Mode
        {
            //Написать функцию конвертирования значения из буффера приема в числовое значение
            Ressieve_String(buf,2);
            Uz_pwm=atoi(buf);
            
        }
        else if(Check_ModeWork()==0)//Manual Mode
        {
            //Написать функцию конвертирования значения АЦП в значения Uz_pwm
            adcVal=ADC_read(ADC_0);
            ConvertSpeed=adcVal*1.96;
            Uz_pwm=ConvertSpeed;
            if(Check_button_direction()==1)//если нажата кнопка меняем знак направления
            {
                Uz_pwm*=-1;
            }
        }
        
        
        if(Uz_pwm>2000)
        {
            Uz_pwm=2000;//верхняя граница положительного диапазона
        }
        if(Uz_pwm<-2000)
        {
            Uz_pwm=-2000;//верхняя граница отрицательного диапазона
        }
        
        if(Uz_pwm>0)//если задание положительно
        {
            switch(Phs_p_pwm1)
            {
                case 0:
                {
                    Phs_n_pwm1=0;
                    Phs_z_pwm1=0;
                    TMR1=0;
                    TMR1IE=1;
                    TMR1ON=1;
                    PORTD=0x0B; //подаем «1» на IN1, SD1, SD2
                    Phs_p_pwm1=1;
                    break;
                }
                case 1:
                {
                    if(TMR1>=Uz_pwm)//счетчик TMR2 превысил значение задания
                    {
                        PORTD = 0x0F; // подаем «1» на IN1, SD1, IN2, SD2
                        Phs_p_pwm1 = 2;
                    }
                    break;
                }
                
                case 3:
                {
                    if(TMR1>=Uz_pwm)// счетчик TMR2 превысил значение задания
                    {
                        PORTD = 0x0A; // подаем «1» на SD1, SD2
                        Phs_p_pwm1 = 4;
                    }
                    break;
                }
            }
        }
        
        if(Uz_pwm<0)//если задание отрицательно
        {
            switch(Phs_n_pwm1)
            {
                case 0:
                {
                    Phs_p_pwm1=0;
                    Phs_z_pwm1=0;
                    TMR1=0;
                    TMR1IE=1;
                    TMR1ON=1;
                    PORTD = 0x0E; // подаем «1» на SD1, IN2, SD2
                    Phs_n_pwm1 = 1;
                    break;
                }
                
                case 2:
                {
                    if(TMR1>=(0-Uz_pwm))//счетчик TMR1 превысил значение задания
                    {
                        
                        PORTD=0x0F;// подаем «1» на IN1, SD1, IN2, SD2
                        Phs_n_pwm1=2;
                    }
                    
                    break;
                }
                
                case 3:
                {
                    if(TMR1>=(0-Uz_pwm))//счетчик TMR2 превысил значение задания
                    {
                        PORTD=0x0A;// подаем «1» на SD1, SD2
                        Phs_n_pwm1 = 4;

                    }
                    break;
                }
            }
        }
    }
}


/*--------------------Инициализация портов МК-----------------*/
void Port_Init(void)
{
    TRISD0=0;   //IN1
    TRISD1=0;   //SD1
    TRISD2=0;   //IN2
    TRISD3=0;   //SD2
    
    TRISC1=0;   //Cooler
    
    TRISC0=1;   //direction button
    TRISB0=1;   //Mode Button(1-USART,0-Manual control)
    
    PORTDbits.RD0=0;
    PORTDbits.RD1=0;
    PORTDbits.RD2=0;
    PORTDbits.RD3=0;
    
    
    
    
    
    
}

/*-------------------Функция нажатия на кнопку направления движения двигателя----------------*/
uint8_t Check_button_direction(void)
{
    uint8_t result=0;
    uint16_t count;
    
    
    while(RC0)
    {
        if(count<COUNT_DELAY)
        {
            count++;
        }
        else
        {
            result=1;
            break;
        }
    }
    return result;
}


/*-----------------Функция проверки режима работы устройства---------------------*/
uint8_t Check_ModeWork(void)
{
    uint8_t result=0;
    uint16_t count;
    while(RB0)
    {
        if(count<COUNT_DELAY)
        {
            count++;
        }
        else
        {
            result=1;
            break;
        }
    }
    return result;
}


/*--------------------Инициализация 16-битного таймера--------------*/
void Timer1_Init(void)
{
    
    /*------Установим предделитель на 2--------*/
    T1CKPS0=1;
    T1CKPS1=0;
    /*-------------*/
    /*---------вкл. тактирование таймера 2*/
    T1OSCEN=1;
    /*------------------*/
    /*----------Тактирование от внутр.генератора*/
    TMR1CS=0;//Fosc/4
    /*----------------------*/
    /*------------вкл. прерывания по переполению--------*/
    //TMR1IE=1;
    
    TMR1=0x0000;
    
}


/*----------------Функция инициализации ШИМ для вентелятора------------------*/
void PWM_Init(void)
{
    PR2 = (_XTAL_FREQ/(freq*4*TMR2PRESCALE)) - 1; //Setting the PR2 formulae using Datasheet
    //PWM Mode
    CCP2M3=1;
    CCP2M2=1;
    //Timer Config
    //ON  prescale 4
    T2CKPS0=1;
    T2CKPS1=0;
    TRISC1=0;//устанавливаем пин на выход
    
    
}

/*----------------------Функция установки значния ШИМ----------*/
void PWM_SetValue(uint16_t val)
{
    if(val<1023)
    {
        val=((float)val /1023)*(_XTAL_FREQ/(freq*TMR2PRESCALE));
         DC2B1=val&1;//save 1 bit
         DC2B0=val&2; // save 0 bit
         CCPR2L = val >> 2; // save other 8 bits
         
         
    }
}






