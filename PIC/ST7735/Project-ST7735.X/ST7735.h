#ifndef ST7735_H
#define	ST7735_H

#include "Main.h"

#define LED_TRIS TRISD7
#define RST_TRIS TRISD5
#define A0_TRIS  TRISD4

#define LED PORTDbits.RD7
#define RST PORTDbits.RD5
#define A0  PORTDbits.RD4

#define SET_A0      A0=1
#define RESET_A0    A0=0

#define LED_ON      LED=1
#define LED_OFF     LED=0

#define RST_SET     RST=1
#define RST_RESET   RST=0



#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D
#define GRAY1   0x8410
#define GRAY2   0x4208


// Длительность паузы в миллисекундах
#define LCD_DELAY         10



#define ST7735_SLEEP_MODE_OFF       0x11
#define ST7735_COLOR_MODE           0x3A
#define ST7735_Direct_OUTPUT        0x36
#define ST7735_ON_DISPLAY           0x29



/*------------------------------Функция передачи команды----------------*/
void ST7735_SendCommand(uint8_t cmd);
/*-------------------------Функция отправки данныех----------*/
void ST7735_SendData(uint8_t data);
/*------------------------Функция инициализации дисплея---------*/
void ST7735_Init(void);

#endif	/* ST7735_H */

