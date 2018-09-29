#include "LTDC.h"

extern volatile uint32_t RGB565_480x272[65280];
extern LTDC_HandleTypeDef hltdc;
uint16_t X_SIZE = 480;
uint16_t Y_SIZE = 272;

/***********************Функция заливки экрана *****************/
void TFT_FillScreen_565(uint32_t color)
{
	uint32_t i;
	uint32_t n = hltdc.LayerCfg[0].ImageHeight*hltdc.LayerCfg[0].ImageWidth;
	for(i=0;i<n;i++)
	{
		*(__IO uint16_t*) (hltdc.LayerCfg[0].FBStartAdress + (i*2)) = (uint16_t) color;
	} 
}

/***********************Функция отрисовки квардарата***************************/
void TFT_FillRectangle_565(uint16_t x1, uint16_t y1,
        uint16_t x2, uint16_t y2, uint16_t color)
{
	uint32_t xpos, ypos;
	if(x1>x2) swap(x1,x2);
	if(y1>y2) swap(y1,y2);
	for(ypos=y1;ypos<=y2;ypos++)
  {
    for(xpos=x1;xpos<=x2;xpos++)
    {
   *(__IO uint16_t*) (hltdc.LayerCfg[0].FBStartAdress + (2*(ypos*hltdc.LayerCfg[0].ImageWidth + xpos))) = (uint16_t)color;
   }
  }
	
	
}
/***********************Функция отрисовки пикселя***************************/
void TFT_DrawPixel_565(uint16_t Xpos, uint16_t Ypos, uint32_t color)
{
   *(__IO uint16_t*) (hltdc.LayerCfg[0].FBStartAdress + (2*(Ypos*hltdc.LayerCfg[0].ImageWidth + Xpos))) = (uint16_t)color;
}


/***********************Функция отрисовки линии***************************/
void TFT_DrawLine_565(uint16_t x1, uint16_t y1,
        uint16_t x2, uint16_t y2, uint16_t color)
{
 int steep = abs(y2-y1)>abs(x2-x1);
 if (steep)
 {
  swap(x1,y1);
  swap(x2,y2);
 }
 if(x1>x2)
 {
  swap(x1,x2);
  swap(y1,y2);
 }
 int dx,dy;
 dx=x2-x1;
 dy=abs(y2-y1);
 int err=dx/2;
 int ystep;
 if(y1<y2) ystep = 1;
 else  ystep = -1;
 for (;x1<=x2;x1++)
 {
  if (steep) TFT_DrawPixel_565(y1,x1,color);
  else TFT_DrawPixel_565(x1,y1,color);
  err-=dy;
  if (err<0)
  {
   y1 += ystep;
   err+=dx;
  }
 }
}


//==============================================================================================================
/**********************************Заливка экрана(+SDRAM)*************************************/
void TFT_FillScreen(uint32_t color)
{
 uint32_t i;
 uint32_t n = hltdc.LayerCfg[0].ImageHeight*hltdc.LayerCfg[0].ImageWidth;
 for(i=0;i<n;i++)
 {
  *(__IO uint32_t*) (hltdc.LayerCfg[0].FBStartAdress + (i*4)) = color;
 }
}


/**********************************Отрисовка пикселя(+SDRAM)*************************************/
void TFT_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t color)
{
 *(__IO uint32_t*) (hltdc.LayerCfg[0].FBStartAdress + (4*(Ypos*hltdc.LayerCfg[0].ImageWidth + Xpos))) = color;
}


/***************************Функция вывода прямоугольника(SDRAM)*****************************/
void TFT_FillRectangle(uint16_t x1, uint16_t y1,
        uint16_t x2, uint16_t y2, uint32_t color)
{
 uint32_t xpos, ypos;
 if(x1>x2) swap(x1,x2);
 if(y1>y2) swap(y1,y2);
 for(ypos=y1;ypos<=y2;ypos++)
 {
  for(xpos=x1;xpos<=x2;xpos++)
  {
   *(__IO uint32_t*) (hltdc.LayerCfg[0].FBStartAdress + (4*(ypos*hltdc.LayerCfg[0].ImageWidth + xpos))) = color;
  }
 } 
}



/***************************Функция вывода линии(SDRAM)*****************************/
void TFT_DrawLine(uint16_t x1, uint16_t y1,
        uint16_t x2, uint16_t y2, uint32_t color)
{
	int steep = abs(y2-y1)>abs(x2-x1);
	if(steep)
	{
		swap(x1,y1);
		swap(x2,y2);
	}
	if(x1>x2)
	{
		swap(x1,x2);
		swap(y1,y2);
	}
	int dx,dy;
	dx=x2-x1;
	dy=abs(y2-y1);
	int err=dx/2;
	int ystep;
	if(y1<y2) ystep=1;
	else ystep=-1;
	for(;x1<=x2;x1++)
	{
		if(steep) TFT_DrawPixel(y1,x1,color);
		else TFT_DrawPixel(x1,y1,color);
		err-=dy;
		if(err<0)
		{
			y1 += ystep;
			err=dx;
		}
	}
}



/********************Функция отрисовки изображения**********/
void TFT_DrawBitmap(uint32_t Xpos, uint32_t Ypos, uint8_t *pbmp)
{

  uint32_t index = 0, ix=0, width = 0, height = 0, bit_pixel = 0;
	uint32_t address;
	index = *(__IO uint16_t *) (pbmp + 10);
	index |= (*(__IO uint16_t *) (pbmp + 12)) << 16;
	/* Read bitmap width */
	width = *(uint16_t *) (pbmp + 18);
	width |= (*(uint16_t *) (pbmp + 20)) << 16;
	/* Read bitmap height */
	height = *(uint16_t *) (pbmp + 22);
	height |= (*(uint16_t *) (pbmp + 24)) << 16;
	/* Read bit/pixel */
	bit_pixel = *(uint16_t *) (pbmp + 28);
	/* Set the address */
	address = hltdc.LayerCfg[0].FBStartAdress + (((X_SIZE*Ypos) + Xpos)*4);
	/* Bypass the bitmap header */
	pbmp += (index + (width * (height - 1) * (bit_pixel/8)));
	if ((bit_pixel/8) == 4)
  {
    TFT_FillScreen(0xFFFF0000);
  }
  else if ((bit_pixel/8) == 2)
  {
    TFT_FillScreen(0xFF00FF00);
  }
  else
  {
		/* Convert picture to ARGB8888 pixel format */
    for(index=0; index < height; index++)
		{
			for(ix=0; ix < width; ix++)
			{
				*(uint32_t *)(address+(ix*4))=convert24to32(*(uint32_t *)(pbmp+(ix*3)));
			}
			address+= (X_SIZE*4);
			pbmp -= width*(bit_pixel/8);
		}
  }
	bit_pixel = 0;
	
}

