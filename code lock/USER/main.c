#include "stm32f10x.h"
#include "delay.h"
#include "layout.h"

u8 PassExist;
u8 Pswd[PASSLEN];

int main(void)
{
	int ret;
	delay_init();
	Layout_init();
	delay_ms(2000);
	if(PassExist)
		if(!Layout_unlock())
			Layout_reset();
	while(1)
	{
		if(Layout_main())
			NVIC_SystemReset();
		ret=Layout_menu();
		switch(ret)
		{
			case 0:
				break;
			case 1:
				Layout_set();
				break;
			case 2:
				Layout_display();
				break;
			case 3:
				Layout_measure();
				break;
			case 4:
				Layout_led();
				break;
			case 5:
				Layout_beep();
				break;
			case 6:
				Layout_solve();
				break;
			default:
				Layout_Test(ret);
				break;
		}
	}
}
