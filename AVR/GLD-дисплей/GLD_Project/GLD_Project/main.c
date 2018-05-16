
#include "Main.h"



int main(void)
{
	char buf[2][12]=
	{
		"Привет мир\0",
		"Пока   мир\0"
	};
    KS108_Init();
	KS108_Clear();
	GLD_Printf_String(0,0,"Hello World ");
	GLD_print_string(1,0,buf[0],sizeof(buf[0])-1);

    while (1) 
    {
    }
}

