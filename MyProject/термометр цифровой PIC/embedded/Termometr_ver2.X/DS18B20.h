/* 
 * File:   DS18B20.h
 * Author: Dante_L_Levi
 *
 * Created on 28 февраля 2018 г., 19:22
 */

#ifndef DS18B20_H
#define	DS18B20_H

#include "Main.h"


void start_meas( void );
void read_meas( void );
void Indicate_LCDTemp(uint8_t flag,uint8_t znakflag);

#endif	/* DS18B20_H */

