#include "dac.h"





void Dac1_Init(void)
{
  
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4)	;
					
	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	
    DAC_Init(DAC_Channel_1,&DAC_InitType);	 

	DAC_Cmd(DAC_Channel_1, ENABLE);  
  
    DAC_SetChannel1Data(DAC_Align_12b_R, 0);  

}
void Dac1_Set_Vol(u16 vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);
}














