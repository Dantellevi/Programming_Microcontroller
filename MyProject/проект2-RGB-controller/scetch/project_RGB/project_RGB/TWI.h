/*
 * TWI.h
 *
 * Created: 12.12.2016 9:56:35
 *  Author: DANTE_L_LEVI
 */ 


#ifndef TWI_H_
#define TWI_H_
#include "Main.h"

void I2C_init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char c);
void I2C_SendByADDR(unsigned char c,unsigned char addr);
unsigned char I2C_ReadByte(void);
unsigned char I2C_ReadLastByte(void);



#endif /* TWI_H_ */