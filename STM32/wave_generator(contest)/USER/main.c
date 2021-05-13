#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "dac.h"
#include "dma.h"
#include "math.h"
#include "OLED_I2C.h"
#include "myiic.h"
#include "pwm.h"

#define LEN_MAX 16384

typedef enum _waveType
{
    WAVE_SQUARE,
    WAVE_SINE,
    WAVE_RAMP,
	WAVE_TRIANGLE,
} waveType;

typedef struct _waveArgs
{
	u16 len;
	u16 arr;
	u16 psc;
} waveArgs;

//32768 is a invalid length(compile failed).
u16 data[LEN_MAX];

//u16 data_len = 1024;
waveArgs args;
u32 freq=20000;
u32 freq_step=1000;
u16 len_max = LEN_MAX-1;
u16 data_vpp = 3300;
//u16 arr=2;
waveType type;

void wave_gen(waveType type, u16 len, u16 vpp);
void reset_all(void);
waveArgs freq2args(u32 freq);

int main(void)
{
	//u32 addr;
    u8 key;
    type = WAVE_SINE;
    delay_init(168);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(115200);
    KEY_Init();
	
	IIC_Init();
	OLED_Init();
	OLED_CLS();
	
	args = freq2args(freq);
//	args.len=200;
//	args.arr=15;
//	args.psc=0;
//	type=WAVE_RAMP;
	reset_all();
	
	
    while (1)
    {
        key = KEY_Scan(0);
        if (key != 0)
        {
            if (key == WKUP_PRES)
            {
                type++;
                type %= 4;
            }
            else if (key == KEY0_PRES)
            {
				freq-=freq_step;
				args = freq2args(freq);
            }
            else if (key == KEY1_PRES)
            {
				//args.arr++;
				freq+=freq_step;
				args = freq2args(freq);
            }
            reset_all();
			OLED_CLS();
			OLED_ShowInt(0,3,freq,2);
        }
    }
}

void wave_gen(waveType type, u16 len, u16 vpp) // vpp ranges from 0 to 3300, standing for 0V to 3.3v
{
    u16 base = 2048;
    double amp = vpp / 3300.0 * 2047.0;
    u16 i;
    if (vpp > 3300)
        vpp = 3300;
    if (type == WAVE_SINE)
    {
        for (i = 0; i < len; i++)
        {
            data[i] = (u16)(base + sin((double)i / len * 6.283185307) * amp);
        }
    }
    else if (type == WAVE_RAMP)
    {
        for (i = 0; i < len; i++)
        {
            data[i] = (u16)(base + ((double)i / len - 0.5) * 2 * amp);
        }
    }
    else if (type == WAVE_SQUARE)
    {
        for (i = 0; i < len / 2; i++)
        {
            data[i] = base + amp;
        }
        for (i = len / 2; i < len; i++)
        {
            data[i] = base - amp;
        }
    }
    else if (type == WAVE_TRIANGLE)
    {
        for (i = 0; i < len / 2; i++)
        {
            data[i] = (u16)(base + ((double)i / len - 0.25) * 4 * amp);
        }
        for (i = len / 2; i < len; i++)
        {
            data[i] = (u16)(base + ((double)(len - i) / len - 0.25) * 4 * amp);
        }
    }
}

void reset_all()
{
	wave_gen(type, args.len, data_vpp);
    DAC_Cmd(DAC_Channel_2, DISABLE);
    DAC_DMACmd(DAC_Channel_2, DISABLE);
    //DMA_Cmd(DMA1_Stream7, DISABLE); //tim2
	DMA_Cmd(DMA2_Stream5, DISABLE); //tim1
    TIM_Cmd(TIM1, DISABLE);
	if(type == WAVE_SQUARE)
	{
		u32 arr_square=84000000/freq-1;
		TIM2_CH1_PWM_Init(arr_square,0);
		TIM_SetCompare1(TIM2,(arr_square+1)/2);
	}
	else
	{
		TIM1_Int_Init(args.arr, args.psc);
		Dac2_Init();
		MYDMA_Config((u32) & (DAC->DHR12R2), (u32)data, args.len);
		TIM_Cmd(TIM1, ENABLE);
	}
}

waveArgs freq2args(u32 freq)
{
	waveArgs tmp;
	double b=168000000;
	double delta[1000][3];
	int i,j;
	int label_i,label_j;
	int max_i,max_j;
	if (freq > 245) // len_max
	{
		tmp.arr = 15; // (arr+1)==16,the mininum number.
		tmp.psc = 0;
		max_i=8;
		max_j=3;
		for (i = 0; i < max_i; i++)
		{
			for (j = 0; j < max_j; j++)
			{
				delta[i][j] = b / ((double)freq * (double)(tmp.arr + 1 + i) * (double)(tmp.psc + 1 + j));
				delta[i][j] = fabs(delta[i][j] - floor(delta[i][j] + 0.5));
				if ((i == 0 && j == 0) || delta[i][j] < delta[label_i][label_j])
				{
					label_i=i;
					label_j=j;
				}
			}
		}
		tmp.len = (u16)(b / ((double)freq * (double)(tmp.arr + 1 + label_i) * (double)(tmp.psc + 1 + label_j)) + 0.5000001);
		tmp.arr += label_i;
		tmp.psc += label_j;
	}
	else
	{
		tmp.len=len_max;
		tmp.psc=0;
		max_i=1000;
		max_j=3;
		for (i = 0; i < max_i; i+=5)
		{
			for (j = 0; j < max_j; j++)
			{
				delta[i][j] = b / ((double)freq * (double)(tmp.len - i) * (double)(tmp.psc + 1 + j));
				delta[i][j] = fabs(delta[i][j] - floor(delta[i][j] + 0.5));
				if ((i == 0 && j == 0) || delta[i][j] < delta[label_i][label_j])
				{
					label_i=i;
					label_j=j;
				}
			}
		}
		tmp.arr=(u16)(b/((double)freq * (double)(tmp.len - label_i) * (double)(tmp.psc + 1 + label_j)) + 0.5000001)-1;
		tmp.len-=label_i;
		tmp.psc+=label_j;
	}
	return tmp;
}
