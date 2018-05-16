#include "RTC.h"

unsigned char RTC_ConvertDEC(unsigned char c)
{

unsigned char ch=((c>>4)*10+(0b00001111&c));

return ch;

}

unsigned char RTC_ConvertBinDec(unsigned char c)
{



unsigned char ch=(((c/10)<<4)|(c%10));

return ch;


}
