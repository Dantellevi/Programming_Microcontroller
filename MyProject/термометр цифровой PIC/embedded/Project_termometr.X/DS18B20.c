#include "DS18B20.h"

uint16_t temp;
#define PLUS 1
#define  MINUS 0
uint8_t ZNAK=PLUS;





/*
 ==================Функция начала измерений=============
 */
void Start_Meas(void)
{
    if(RC0)
    {
        OneWire_Command(CONVERT_T,NULL);
        W1_PIN=1;
        W1_DDR=0;
        
    }
    else
    {
        
    }
}



void Read_Meas(void)
{
    uint8_t id[8],diff;
    char s[20];
    uint8_t byte[2];
    uint8_t i;
    
    
    for(diff = SEARCH_FIRST; diff != LAST_DEVICE; )
    {
        diff=OneWire_ROM_Search(diff, id);
        if( diff == PRESENCE_ERR )
        {
            //No Sensor Found!!!!
            break;
        }
        if( diff == DATA_ERR )
        {
			//BUS ERROR
			break;
		}
        
        
        if(id[0]==0x28 || id[0]==0x10)  // temperature sensor
        {
            //Print ID:
            
            for( i = 0; i < 8; i++ )
            {
				//sprintf(s, "%02X ", id[i] );
				//print s
            }
            OneWire_byte_WR(READ);// read command
            
            temp=OneWire_Byte_RD();// low byte
            temp |= (unsigned int)OneWire_Byte_RD() << 8;		// high byte
            byte[0]=temp>>8;		//старшая часть
            
            if (byte[0]&0x80)
			{
				temp=~temp;
				temp+=1;
				ZNAK=MINUS;
			}
			else
			{
				ZNAK=PLUS;
			}
            
            switch(ZNAK)
			{
				case PLUS:
				{
					if( id[0] == 0x10 )			// 9 -> 12 bit
					temp <<= 3;
					//sprintf( s, "  T: %04X = ", temp );	// hex value
					//температура код
					//sprintf( s, "Tcels=%4d.%01d C\r\n", temp >> 4, (temp << 12) / 6553 ); // 0.1шC
					//температура в цельсиях;
                    LCD_PrintStringXY(s,1,1);
					break;
				}
				case MINUS:
				{
					if( id[0] == 0x10 )			// 9 -> 12 bit
					temp <<= 3;
					//sprintf( s, "  T: %04X = ", temp );	// hex value
					//температура код
					//sprintf( s, "Tcels=-%4d.%01d C\r\n", temp >> 4, (temp << 12) / 6553 ); // 0.1шC
					//температура в цельсиях;
                    LCD_PrintStringXY(s,1,1);
					break;
				}
			}
            
        }
        
        
        
        
    }
         
}

uint16_t GetTempS(void)
{
    return temp >> 4;
}

uint16_t GetTempM(void)
{
    return (temp << 12) / 6553;
}

uint8_t GetZnak(void)
{
    return ZNAK;
}








