#include "stm32f10x.h"
#include "delay.h"
#include "bitband.h"

char data[41];

uint8_t b2c(char *addr)
{
	uint8_t base = 1, res = 0;
	char *ptr;
	for (ptr = addr + 7; ptr >= addr; ptr--)
	{
		if (*ptr == '1')
			res += base;
		base *= 2;
	}
	return res;
}

void Sensor_Init()
{
	GPIO_InitTypeDef GPIO_IStrc;
	int i = 0;

	for (i = 0; i < 40; i++)
		data[i] = '2';
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOG, ENABLE);
	GPIO_IStrc.GPIO_Pin = GPIO_Pin_8;
	GPIO_IStrc.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_IStrc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_IStrc);
}
int Sensor_Measure(int *tempd,int *tempf, int *humid, int *humif)
{
	u8 i, count, res[5];
	GPIO_InitTypeDef GPIO_IStrc;

	GPIO_IStrc.GPIO_Pin = GPIO_Pin_11;
	GPIO_IStrc.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_IStrc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_IStrc);

	PGout(11) = 0;
	delay_ms(20);
	PGout(11) = 1;
	delay_us(30);
	GPIO_IStrc.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOG, &GPIO_IStrc);
	delay_us(20);
	if (PGin(11) == 0)
	{
		while (PGin(11) == 0)
			;
		while (PGin(11) == 1)
			;
		for (i = 0; i < 40; i++)
		{
			while (PGin(11) == 0)
				;
			for (count = 0; PGin(11) == 1; count += 5)
				delay_us(5);
			if (count < 50)
				data[i] = '0';
			else
				data[i] = '1';
		}
		delay_us(150);
		data[40] = '\0';
		for (i = 0; i < 5; i++)
			res[i] = b2c(data + 8 * i);
		if (res[4] == res[0] + res[1] + res[2] + res[3])
		{
			*humid = res[0];
			*humif = res[1];
			*tempd = res[2];
			*tempf = res[3];
			return 0;
		}
		else
			return 1;
	}
	else
		return 2;
}