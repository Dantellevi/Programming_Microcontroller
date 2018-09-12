#include "SPI.h"

/*------------------------------------Инициализация SPI-интерфейса-----------------------*/
void SpiInit(Spi_type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
    TRISC5=0;
    if(sType & 0b00000100)  //если ведомый режим
    {
        SSPSTAT=sTransmitEdge;//устанавливаем статусный регистр
        TRISC3=1;
        
    }
    else    //мастер
    {
        SSPSTAT=sDataSample|sTransmitEdge; //настраиваем выборку данных и устанавливаем режим перехода в передачу данных
        TRISC3=0;
        SS_TRIS=0;
        
    }
    SSPCON1=sType|sClockIdle;//устанавливаем делитель и тактирование по низкому или высокому уровню
    
}

/*------------------------Ожидание завершения приема-----------------*/
static void SpiReceiveWait(void)
{
    while(!SSPSTATbits.BF);//дожидаемся завершения приема данных
}



/*-----------------Запись данных в шину--------------*/
void SPI_Write_Data(uint8_t dat)
{
    SSPBUF=dat;
}


/*
 ==================Проверка данных для чтения===========
 */
unsigned spiDataReady(void) 
{
  if(SSPSTATbits.BF)
    return 1;
  else
    return 0;
}


/*
 =============Чтение данных из Шины==============
 */
char spiRead(void) // Чтение полученных данных
{
  SpiReceiveWait(); // Подождите, пока все биты не получат
  return (SSPBUF); // Чтение полученных данных из буфера
}








