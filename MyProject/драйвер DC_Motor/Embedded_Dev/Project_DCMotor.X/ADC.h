#ifndef ADC_H
#define	ADC_H


#include "Main.h"



#define ADC_0 0
#define ADC_1 1
#define ADC_2 2
#define ADC_3 3
#define ADC_4 4
#define ADC_5 5
#define ADC_6 6




/*----------------Функция инициализации АЦП-------------*/
void ADC_Init(float Uref);
/*-------------------Функция чтения значения АЦП-----------*/
uint16_t ADC_read(uint8_t channel);
/*--------------------функция получения значения напряжения-----------------*/
float Get_Voltage(uint8_t channel);

/*----------------Функция получения скорости с потенциометра-------------*/
uint16_t Get_Speed(uint8_t c);



#endif	/* ADC_H */

