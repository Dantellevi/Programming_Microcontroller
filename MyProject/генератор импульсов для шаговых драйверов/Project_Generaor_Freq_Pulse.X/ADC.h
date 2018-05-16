/* 
 * File:   ADC.h
 * Author: Dante_L_Levi
 *
 * Created on 29 марта 2018 г., 10:48
 */

#ifndef ADC_H
#define	ADC_H

#include "Main.h"

#define ADCCHannel_0 0
#define ADCCHannel_1 1
#define ADCCHannel_2 2
#define ADCCHannel_3 3
#define ADCCHannel_4 4
#define ADCCHannel_5 5
#define ADCCHannel_6 6
#define ADCCHannel_7 7




/*
 =========================Функция инициализации АЦП=======================
 * Принимаемые параметры:
 *          
 */
void ADC_Init(uint8_t Uref);

/*
    ---------------------------------Функция чтения данных из регистра АЦП---------------------
 *                      Принимаемые параметры:
 *                          channel-канал по которому будет считыватся значения
 *                      Возращаемое значение:
 *                          данные из регистра АЦП
 */
uint16_t ADC_Read(uint8_t channel);

#endif	/* ADC_H */

