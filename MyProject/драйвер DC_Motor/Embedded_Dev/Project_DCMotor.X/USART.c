#include "USART.h"




/*----------------Функция инициализации UART интерфейса-------------------*/
void Usart_Init(int32_t baud)
{
    uint16_t x;
    x=((_XTAL_FREQ-baud*64)/(baud*64));
    if(x>255)
    {
        x = (_XTAL_FREQ - baud*16)/(baud*16); //SPBRG for High Baud Rate
        SPBRG = x; //write Data registr speed
        
        
    }
    if(x<256)
    {
        SYNC=1;//отк. синхронный режим(устанавливаем ассинхронный режим))
        SPEN=1;//вкл. разрешение работы порта
        TRISC7=1;  //пин RxD устанавливаем на вход
        TRISC6=0;  //пин TxD устанав. на выход
        CREN=1;//неприрывный прием данных
        TXEN=1;//вкл. передачу данных 
    }
}


/*-----------------Функция передачи символа по USART--------------*/
void Transmit_char(char data)
{
    while(!TRMT);       //ожидаем флага разрешения передачи
    TXREG=data;
}


/*--------------------Функция проверки флага передачи-------------*/
char UART_TX_Emty(void)
{
    return TRMT;
}


/*------------------Функция вывода строки в терминал----------*/
void Uart_PrintString(char *buffer)
{
    uint8_t i=0;
    for(i=0;buffer[i]!='\0';i++)
    {
        Transmit_char(buffer[i]);
    }
    Transmit_char(0x0D);
    Transmit_char(0x0A);
}


/*---------------------Функция считывания одиночного символа----------*/
char Uart_Read(void)
{
    while(!RCIF);
    return RCREG;
}


/*-------------------Функция приема строки из терминал-----------*/
void Ressieve_String(char *buffer,uint16_t length)
{
    uint16_t i;
    for(i=0;i<length;i++)
    {
        buffer[i]=Uart_Read();
    }
}


