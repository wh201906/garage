#include "dma.h"

void MYDMA_Config(u32 cpar,u32 cmar,u16 cndtr) // tim1
{
	DMA_InitTypeDef DMA_InitStructure;

 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	DMA_DeInit(DMA2_Stream5); // important

	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_Channel = DMA_Channel_6; 
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;
	DMA_InitStructure.DMA_Memory0BaseAddr = cmar;
	DMA_InitStructure.DMA_BufferSize = cndtr;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	

	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	  
	  
	
	DMA_Init(DMA2_Stream5, &DMA_InitStructure);
	DMA_Cmd(DMA2_Stream5, ENABLE);
}   

//void MYDMA_Config(u32 cpar,u32 cmar,u16 cndtr) //tim2
//{
//	DMA_InitTypeDef DMA_InitStructure;

// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
//	
//	DMA_DeInit(DMA1_Stream7); // important

//	DMA_StructInit(&DMA_InitStructure);
//	DMA_InitStructure.DMA_Channel = DMA_Channel_3; 
//	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;
//	DMA_InitStructure.DMA_Memory0BaseAddr = cmar;
//	DMA_InitStructure.DMA_BufferSize = cndtr;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; 
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//	

//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//	  
//	  
//	
//	DMA_Init(DMA1_Stream7, &DMA_InitStructure);
//	DMA_Cmd(DMA1_Stream7, ENABLE);
//} 
 

























