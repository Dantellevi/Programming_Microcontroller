#include "Main.h"


void main(void) {
    
    LCD_Init(0);
    LCD_Clear();
    LCD_PrintStringXY("Hello World",0,0);
    USART_Init(9600);
    __delay_ms(1000);
    LCD_Clear();
    
    
    while(1)
    { 
      start_meas();
		 __delay_ms(1000);
		 read_meas();
         
         __delay_ms(1000);
    }
    
}
