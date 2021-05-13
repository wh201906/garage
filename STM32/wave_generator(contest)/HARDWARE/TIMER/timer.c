#include "timer.h"
#include "led.h"
#include "dac.h"

void TIM2_Int_Init(u16 arr,u16 psc) // 84MHz
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_PrescalerConfig(TIM2,psc,TIM_PSCReloadMode_Update);
	TIM_SetAutoreload(TIM2, arr);
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
	TIM_Cmd(TIM2, ENABLE);
	TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE);

}


void TIM1_Int_Init(u16 arr,u16 psc) // 168MHz
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_PrescalerConfig(TIM1,psc,TIM_PSCReloadMode_Update);
	TIM_SetAutoreload(TIM1, arr);
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);
	TIM_Cmd(TIM1, ENABLE);
	TIM_DMACmd(TIM1, TIM_DMA_Update, ENABLE);

}








