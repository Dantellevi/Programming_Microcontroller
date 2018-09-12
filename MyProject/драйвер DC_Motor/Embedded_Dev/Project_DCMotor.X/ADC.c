#include "ADC.h"

float Vref=0;//переменная хранящая опорное напряжения МК


/*----------------Функция инициализации АЦП-------------*/
void ADC_Init(float Uref)
{
    /*------------Настройка тактирование АЦП----------*/
    ADCS2=1;    //Тактирование F/4
    ADCS1=0;
    ADCS0=0;
    /*-----------------------------------------------**/
    ADON=1;//вкл. разрешение преобразования
    /*------------------------------------------------*/
    ADFM=1;//бит отвечающий за формат преобразования
    
    Vref=Uref;
}



/*-------------------Функция чтения значения АЦП-----------*/
uint16_t ADC_read(uint8_t channel)
{
    
    if(channel>12)
    {
        return 0;
       
    }
    else
    {
        ADCON0&=0xC5;//производим маскирование
        ADCON0|=channel<<3;
         __delay_ms(2);
        GO_nDONE = 1;//: A/D Conversion Status bit
        while(GO_nDONE);//wait
        return ((ADRESH<<8)+ADRESL);
    }
    


}

/*----------------Функция получения скорости с потенциометра-------------*/
uint16_t Get_Speed(uint8_t c)
{
    return ADC_read(c);
}


/*--------------------функция получения значения напряжения-----------------*/
float Get_Voltage(uint8_t channel)
{
    float  voltage=((ADC_read(channel)*Vref)/1024);
    return voltage;
}




