/* 
 * File:   DS18B20.h
 * Author: Dante_L_Levi
 *
 * Created on 25 апреля 2018 г., 22:01
 */

#ifndef DS18B20_H
#define	DS18B20_H

#include "Main.h"
#include <string.h>



/*
 ==================Функция начала измерений=============
 */
void Start_Meas(void);
void Read_Meas(void);
uint16_t GetTempS(void);
uint16_t GetTempM(void);
uint8_t GetZnak(void);


#endif	/* DS18B20_H */

