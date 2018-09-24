#include "I2C.h"

extern uint8_t aTxBuffer[8];//буффер для приема и передачи данных через I2C
extern I2C_HandleTypeDef hi2c1;
char str[24];


/*************************Функция записи в устройство с определенным адресом************************/
void I2C_WriteBuffer(uint8_t ADDR,uint8_t sizebuf)
{
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)ADDR,(uint8_t*) &aTxBuffer,(uint16_t)sizebuf, (uint32_t)1000)!=HAL_OK)
	{
		 if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)

                        {
                                sprintf(str, "Buffer error");
                                //LCD_SetPos(8, 0);
                                //LCD_String(str);

                        }
	}
}


/*************************Функция чтения из устройство с определенным адресом************************/
void I2C_ReadBuffer(uint8_t ADDR,uint8_t sizebuf)
{
	while(HAL_I2C_Master_Receive(&hi2c1,(uint16_t)ADDR,(uint8_t*) &aTxBuffer,(uint16_t)sizebuf, (uint32_t)1000)!=HAL_OK)
	{
		 if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)

                        {
                                sprintf(str, "Buffer error");
                                //LCD_SetPos(8, 0);
                                //LCD_String(str);

                        }
	}
}

