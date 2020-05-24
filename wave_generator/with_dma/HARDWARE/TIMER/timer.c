#include "timer.h"
#include "led.h"
#include "dac.h"

void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_DeInit(TIM2); // important
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = arr;	
	TIM_TimeBaseStructure.TIM_Prescaler = psc;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);

}


