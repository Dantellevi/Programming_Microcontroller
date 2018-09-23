
#ifndef __LTDC_H__
#define __LTDC_H__

#include "main.h"
#include "stm32f7xx_hal.h"
#include "stdint.h"
#include "stdio.h"
#include <stdlib.h>
#define swap(a,b) {int16_t t=a;a=b;b=t;}



/***********************Функция заливки экрана *****************/
void TFT_FillScreen_565(uint32_t color);


//***********************Функция отрисовки квардарата***************************/
void TFT_FillRectangle_565(uint16_t x1, uint16_t y1,
        uint16_t x2, uint16_t y2, uint16_t color);
/***********************Функция отрисовки пикселя***************************/
void TFT_DrawPixel_565(uint16_t Xpos, uint16_t Ypos, uint32_t color);
/***********************Функция отрисовки линии***************************/
void TFT_DrawLine_565(uint16_t x1, uint16_t y1,
        uint16_t x2, uint16_t y2, uint16_t color);
/******************************************************************************/


/**********************************Заливка экрана(+SDRAM)*************************************/
void TFT_FillScreen(uint32_t color);
/**********************************Отрисовка пикселя(+SDRAM)*************************************/
void TFT_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t color);

/***************************Функция вывода прямоугольника(SDRAM)*****************************/
void TFT_FillRectangle(uint16_t x1, uint16_t y1,
        uint16_t x2, uint16_t y2, uint32_t color);
/***************************Функция вывода линии(SDRAM)*****************************/
void TFT_DrawLine(uint16_t x1, uint16_t y1,
        uint16_t x2, uint16_t y2, uint32_t color);





#endif /* __LTDC_H__ */



