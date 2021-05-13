#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "dac.h"
 

 int main(void)
 {		
	u8 key;
	extern u8 mode;
	extern u16 divider;
	delay_init();	    	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	uart_init(115200);	 
 	LED_Init();			     
	TIM3_Int_Init(49,71);
	Dac1_Init();
	KEY_Init();
   	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)
		{
			mode++;
			mode%=3;
			if(mode==0)
				divider=2;
			else
				divider=300;
		}
		else if(key==KEY1_PRES)
		{
			TIM3->ARR=(TIM3->ARR+1)*2-1;
		}
		else if(key==WKUP_PRES)
		{
			TIM3->ARR=(TIM3->ARR+1)/2-1;
		}
	}	 

 
}	 
 
