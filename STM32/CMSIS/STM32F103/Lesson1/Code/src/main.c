#include "stm32f10x.h"


void Delay(uint32_t del)
{
	uint32_t i;
	for(i=0;i<del;i++){}
}


int main(void)
{
	
	RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;
	GPIOC->CRH|=GPIO_CRH_MODE13_0;		//выставляет на выход с мах частотой 10МГц
	GPIOC->CRH&=~GPIO_CRH_CNF13;	//выставляем ножку на выход(push-pull)
	
	GPIOC->ODR&=~GPIO_ODR_ODR13;
	
	while(1)
	{
  		GPIOC->ODR|=GPIO_ODR_ODR13;	//устанавливаем 1
  		Delay(10000000);
  		GPIOC->ODR&=~GPIO_ODR_ODR13;//выставляем ноль на выход пина PC13
  		Delay(10000000);
	}
}

