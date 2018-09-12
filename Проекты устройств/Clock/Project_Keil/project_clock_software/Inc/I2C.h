
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdint.h"

/*************************Функция записи в устройство с определенным адресом************************/
void I2C_WriteBuffer(uint8_t ADDR,uint8_t sizebuf);
/*************************Функция чтения из устройство с определенным адресом************************/
void I2C_ReadBuffer(uint8_t ADDR,uint8_t sizebuf);


#endif /* __I2C_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



