
#ifndef __LTDC_H__
#define __LTDC_H__

#include "main.h"
#include "stm32f7xx_hal.h"
#include "stdint.h"
#include "stdio.h"

#define swap(a,b) {int16_t t=a;a=b;b=t;}



/***********************Функция заливки экрана *****************/
void TFT_FillScreen(uint32_t color);


//***********************Функция отрисовки квардарата***************************/
void TFT_FillRectangle(uint16_t x1, uint16_t y1,
        uint16_t x2, uint16_t y2, uint16_t color);
/***********************Функция отрисовки пикселя***************************/
void TFT_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t color);
/***********************Функция отрисовки линии***************************/
void TFT_DrawLine(uint16_t x1, uint16_t y1,
        uint16_t x2, uint16_t y2, uint16_t color);



#endif /* __LTDC_H__ */



