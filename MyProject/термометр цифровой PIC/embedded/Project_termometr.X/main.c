#include "Main.h"


void main(void) {
    
    LCD_Init(0);
    LCD_Clear();
    //LCD_PrintStringXY("Hello World",0,0);
    uint16_t TempS;
    uint16_t TempM;
    Start_Meas();
    while(1)
    {
        
        Read_Meas();
        TempS=GetTempS();
        TempM=GetTempM();
        //sprintf(buf,"T=%4d.%01d C",GetTempS(),GetTempM());
        if(GetZnak()==1)
        {
           //sprintf(buf,"T=+ %4d.%01d C",GetTempS(),GetTempM());
           LCD_PrintStringXY(" +",0,0); 
        }
        else if(GetZnak()==0)
        {   
           // sprintf(buf,"T=- %4d.%01d C",GetTempS(),GetTempM());
            LCD_PrintStringXY(" -",0,0); 
            
        }
       
        //LCD_PrintStringXY(buf,5,0); 
    }
    
}
