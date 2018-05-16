#include "TWI.h"

void I2C_init(void)
{
TWBR=0x20;//скорость передачи (100к√ц при 8 ћ√ц)

}

void I2C_Start(void)
{
TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
while(!(TWCR&(1<<TWINT)));

}
void I2C_Stop(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	

}

void I2C_SendByte(unsigned char c)
{
TWDR=c;
TWCR=(1<<TWINT)|(1<<TWEN);
while(!(TWCR&(1<<TWINT)));

}


void I2C_SendByADDR(unsigned char c,unsigned char addr)
{

I2C_Start();
I2C_SendByte(addr);
I2C_SendByte(c);
I2C_Stop();

}

unsigned char I2C_ReadByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}

unsigned char I2C_ReadLastByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}