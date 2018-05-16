#include "Main.h"
#include <string.h>


void main(void)
{
    char buf[20]="Hello World!!";
    GLDKS108_Init();
    GLD_print_string(0,0,buf,strlen(buf));
    GLD_Printf_String(1,5,"PIC18F4515!!");
    GLD_Draw_Ellipse(40,40,10);
    while(1)
    {
        
    }
}



