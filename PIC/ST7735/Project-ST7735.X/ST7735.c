#include "ST7735.h"

void Transmit_Data(uint8_t data)
{
    SS_Strob_OFF;
    
   __delay_ms(1);
    SPI_Write_Data(data);
    
    SS_Strob_ON;
}

/*------------------------------Функция передачи команды----------------*/
void ST7735_SendCommand(uint8_t cmd)
{
    RESET_A0;//отправляем команду
    Transmit_Data(cmd);
}


/*-------------------------Функция отправки данныех----------*/
void ST7735_SendData(uint8_t data)
{
    SET_A0;//отправляем данные
    Transmit_Data(data);
}



/*------------------------Функция инициализации дисплея---------*/
void ST7735_Init(void)
{
    SpiInit(SPI_MASTER_OSC_DEL4,SPI_DATA_SAMPLE_MIDDLE,SPI_CLOCK_IDLE_LOW,SPI_IDLE_2_ACTIVE);
    
    SS_TRIS=0;
    A0_TRIS=0;
    RST_TRIS=0;
    LED_TRIS=0;
    
    SS_Strob_ON;
    RST_SET;//аппаратный сброс
    __delay_ms(LCD_DELAY);
    RST_RESET;
    __delay_ms(LCD_DELAY);
    
    ST7735_SendCommand(ST7735_SLEEP_MODE_OFF);
    __delay_ms(LCD_DELAY);
    ST7735_SendCommand(ST7735_COLOR_MODE);
    ST7735_SendData(0x05);
    ST7735_SendCommand(ST7735_Direct_OUTPUT);
    ST7735_SendCommand(ST7735_ON_DISPLAY);
    
    
    SS_Strob_OFF;
    
    
    
    
}










