#include "DS18B20.h"


unsigned int temp;
uint16_t Tvnesh;
uint16_t Tvnyt;

#define PLUS 1
#define  MINUS 0
unsigned char ZNAK=PLUS;



void start_meas( void ){
	if( OWIREINPIN==1){
		OneWire_command( CONVERT_T, NULL );
		SETPINWIRE;
		TRISWIREOUT;			// parasite power on

		}else{
		Usart_PrintString( "Short Circuit !\r\n" );
	}
}



void read_meas( void )
{
	unsigned char id[8], diff;
	char s[30];
    char sid[30];
	unsigned char byte[2];
	unsigned char i;
	
    uint8_t count=0;
	for( diff = SEARCH_FIRST ; diff != LAST_DEVICE;count++ ){
		diff = w1_rom_search( diff, id );
        
        
		if( diff == PRESENCE_ERR ){
			LCD_PrintStringXY( "No Sensor found",0,3 );
			Usart_PrintString( "No Sensor found\r\n" );
            break;
		}
        else
        {
            LCD_PrintStringXY( "CONNECTION OK  ",0,3 );
            Usart_PrintString( "CONNECTION OK  \r\n" );
        }
       
        
		if( diff == DATA_ERR ){
			LCD_PrintStringXY( "Bus Error      ",0,3 );
            Usart_PrintString( "Bus Error\r\n" );
			
		}
        else
        {
            LCD_PrintStringXY( "CONNECTION OK  ",0,3 );
            Usart_PrintString( "CONNECTION OK  \r\n" );
        }
		if( id[0] == 0x28 || id[0] == 0x10 )
        {	// temperature sensor
			Usart_PrintString( "ID: " );
			for( i = 0; i < 8; i++ ){
				sprintf(s, "%02X ", id[i] );
				
                Usart_PrintString(s);
			}
			OneWire_Byte_Write( READ );			// read command
				
			
			temp = OneWire_Byte_Read();			// low byte
			temp |= (unsigned int)OneWire_Byte_Read() << 8;		// high byte
			
            byte[0]=temp>>8;		//ñòàðøàÿ ÷àñòü
             
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
                    if(count==0)
                    {
                        Tvnesh=temp;
                    }
                    else if(count==1)
                    {
                        Tvnyt=temp;
                    }
					//sprintf( s, "  T: %04X = ", temp );	// hex value
					//LCD_PrintStringXY(s,0,0);
                   Indicate_LCDTemp(count,PLUS);
					sprintf( s, "Tcels=%4d.%01d C\r\n", temp >> 4, (temp << 12) / 6553 ); // 0.1øC
					//LCD_PrintStringXY(s,0,0);
                    Usart_PrintString(s);
					break;
				}
				case MINUS:
				{
					if( id[0] == 0x10 )			// 9 -> 12 bit
					temp <<= 3;
					//sprintf( s, "  T: %04X = ", temp );	// hex value
					//Usart_PrintString(s);
                    if(count==0)
                    {
                        Tvnesh=temp;
                    }
                    else if(count==1)
                    {
                        Tvnyt=temp;
                    }
                    Indicate_LCDTemp(count,MINUS);
					sprintf( s, "Tcels=-%4d.%01d C\r\n", temp >> 4, (temp << 12) / 6553 ); // 0.1øC
					//LCD_PrintStringXY(s,0,0);
                    Usart_PrintString(s );
					break;
				}
			}
            
            
			
			
				
			
						
			
			
			
		}
	}
	Usart_PrintString( "" );
}



void Indicate_LCDTemp(uint8_t flag,uint8_t znakflag)
{
    char bufferVn[30];
    char bufferVnyt[30];
    char byte[2];
    switch(flag)
    {
        case 0:
        {
            if(znakflag==PLUS)
            {
                sprintf(bufferVn,"Tvnesh=+%4d.%01d C",Tvnesh >> 4, (Tvnesh << 12) / 6553);
                
            }
            else if(znakflag==MINUS)
            {
                sprintf(bufferVn,"Tvnesh=-%4d.%01d C",Tvnesh >> 4, (Tvnesh << 12) / 6553);
            }
            LCD_PrintStringXY(bufferVn,0,1);
            break;
        }
        case 1:
        {
            if(znakflag==PLUS)
            {
                sprintf(bufferVnyt,"Tvnyt=+%4d.%01d C",Tvnyt >> 4, (Tvnyt << 12) / 6553);
            }
            else if(znakflag==MINUS)
            {
                sprintf(bufferVnyt,"Tvnyt=-%4d.%01d C",Tvnyt >> 4, (Tvnyt << 12) / 6553);
            }
            LCD_PrintStringXY(bufferVnyt,0,2);
            break;
        }
    }
    
    
    
    
    
    
}