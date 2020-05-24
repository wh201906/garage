#include "dma.h"

void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;

 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	
	DMA_DeInit(DMA_CHx); // important

	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; 
	DMA_InitStructure.DMA_BufferSize = cndtr;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  
	
	DMA_Init(DMA_CHx, &DMA_InitStructure);
	DMA_Cmd(DMA_CHx, ENABLE);
}   

 







