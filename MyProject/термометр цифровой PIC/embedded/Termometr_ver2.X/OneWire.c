#include "OneWire.h"

uint8_t OneWire_reset(void)
{
    uint8_t err;
    RESETPINWIRE;   //выставляем на ноге 0
    TRISWIREOUT;  //конфигурируем на выход
    __delay_us(480);
    TRISWIREINPUT;  //конфигурируем на вход
    __delay_us(66);
    err=W1_PIN_PORT&(1<<W1_PIN);        //считываем значения с пина
    __delay_us(480-66);
    if(OWIREINPIN==0)
    {
        err=1;
    }
    
    return err;
    
}



uint8_t OneWire_Bit_IO(uint8_t b)
{
    TRISWIREOUT;    //выставляем пин на выход
    __delay_us(1);
    if(b)
    {
        TRISWIREINPUT;  //конфигурируем на вход
        
    }
    __delay_us(14);
    if(OWIREINPIN==0)
    {
        b=0;
    }
    
    __delay_us(45);
    TRISWIREINPUT;
    return b;
}


uint16_t OneWire_Byte_Write(uint8_t b)
{
    uint8_t i=8,j;
    
    do{
        j=OneWire_Bit_IO(b&1);
        b>>=1;
        if(j)
        {
            b|=0x80;
        }
    }while(--i);
    return  b;
}

uint16_t OneWire_Byte_Read(void)
{
    return OneWire_Byte_Write(0xFF);
}



uint8_t w1_rom_search( uint8_t diff, uint8_t *id )
{
	uint8_t i, j, next_diff;
	uint8_t b;

	if( OneWire_reset() )
	return PRESENCE_ERR;			// error, no device found
	OneWire_Byte_Write( SEARCH_ROM );			// ROM search command
	next_diff = LAST_DEVICE;			// unchanged on last device
	i = 8 * 8;					// 8 bytes
	do{
		j = 8;					// 8 bits
		do{
			b = OneWire_Bit_IO( 1 );			// read bit
			if( OneWire_Bit_IO( 1 ) ){			// read complement bit
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
			OneWire_Bit_IO( b );     			// write bit
			*id >>= 1;
			if( b )					// store bit
			*id |= 0x80;
			i--;
		}while( --j );
		id++;					// next byte
	}while( i );
	return next_diff;				// to continue search
}





void OneWire_command( uint8_t command, uint8_t *id )
{
	unsigned char i;
	OneWire_reset();
	if( id ){
		OneWire_Byte_Write( MATCH_ROM );			// to a single device
		i = 8;
		do{
			OneWire_Byte_Write( *id );
			id++;
		}while( --i );
		}else{
		OneWire_Byte_Write( SKIP_ROM );			// to all devices
	}
	OneWire_Byte_Write( command );
}

