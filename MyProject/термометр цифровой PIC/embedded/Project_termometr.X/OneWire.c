#include "OneWire.h"

/*
 =================Функция перезапуска интерфейса======
 */
uint8_t oneWire_Reset(void)
{
    uint8_t err;
    W1_OUT=0;
    TRISC0=0;
    __delay_us(480);
    TRISC0=1;
    __delay_us(66);
    if(W1_IN==1)
    {
        err=1;
    }
    else if(W1_IN==0)
    {
        err=0;
    }
    __delay_us(480-66);
    if(!W1_IN)
    {
        err=1;
    }
    
    return err;
    
    
}


/*
 ====================Чтение запись бита==============
 */
uint8_t OneWire_bit_IO(uint8_t b)
{
    TRISC0=0;
    __delay_us(1);
    if(b)
    {
       TRISC0=1; 
    }
    __delay_us(14);
    if(!W1_IN)
    {
        b=0;
    }
    __delay_us(45);
    TRISC0=1;
    
    return b;
}


/*
 =========================Функция записи байта=========
 */
uint16_t OneWire_byte_WR(uint8_t b)
{
    uint8_t i=8,j;
    do{
        j=OneWire_bit_IO(b&1);
        b>>=1;
        if(j)
        {
            b|=0x80;
        }
        
    }while(--i);
    return b;
}


/*
 ================Функция чтения байта===============
 */
uint16_t OneWire_Byte_RD(void)
{
    return OneWire_byte_WR(0xFF);
}


/*
 ============================Функция получения кода устройства===========
 */
uint8_t OneWire_ROM_Search(uint8_t diff,uint8_t *id)
{
    uint8_t i,j,next_diff;
    uint8_t b;
    
    if(oneWire_Reset())
    {
        return PRESENCE_ERR;// error, no device found
    }
    OneWire_byte_WR(SEARCH_ROM);// ROM search command
    next_diff=LAST_DEVICE;// unchanged on last device
    
    i=8*8;// 8 bytes
    do
    {
        j=8;// 8 bits
        do
        {
          b = OneWire_bit_IO( 1 );			// read bit
			if( OneWire_bit_IO( 1 ) ){			// read complement bit
				if( b )					// 11
				return DATA_ERR;			// data error
				}else{
				if( !b ){				// 00 = 2 devices
					if( diff > i ||
					((*id & 1) && diff != i) ){
						b = 1;				// now 1
						next_diff = i;			// next pass 0
					}
				}
			}
			OneWire_bit_IO( b );     			// write bit
			*id >>= 1;
			if( b )					// store bit
			*id |= 0x80;
			i--;  
        }while(--j);
        id++;
    }while(i);
    
    return next_diff;
    
}


/*
 =============================Функция передачи команды==============
 */
void OneWire_Command(uint8_t command,uint8_t *id)
{
    uint8_t i;
    oneWire_Reset();
    if(id)
    {
        OneWire_byte_WR(MATCH_ROM);
        i=8;
        do
        {
           OneWire_byte_WR(*id);
           id++;
        }while(--i);
    }
    else
    {
        OneWire_byte_WR(SKIP_ROM);
    }
    OneWire_byte_WR(command);
}






