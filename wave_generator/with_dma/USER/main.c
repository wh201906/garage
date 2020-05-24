#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "dac.h"
#include "dma.h"
#include "math.h"

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
u32 freq=10000;
u32 freq_step=100;
u16 len_max = LEN_MAX-1;
u16 data_vpp = 3300;
//u16 arr=2;
waveType type;

void wave_gen(waveType type, u16 len, u16 vpp);
void reset_all(void);
waveArgs freq2args(u32 freq);

int main(void)
{
    u8 key;
    type = WAVE_SINE;
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(115200);
    LED_Init();
    KEY_Init();
    //reset_all();
	
	args = freq2args(freq);
//	args.len=1638;
//	args.arr=439;
//	type=WAVE_RAMP;
	reset_all();
	
    while (1)
    {
        key = KEY_Scan(0);
        if (key != 0)
        {
            if (key == KEY0_PRES)
            {
                type++;
                type %= 4;
            }
            else if (key == KEY1_PRES)
            {
				freq-=freq_step;
				args = freq2args(freq);
            }
            else if (key == WKUP_PRES)
            {
				//args.arr++;
				freq+=freq_step;
				args = freq2args(freq);
            }
			else if (key == KEY2_PRES)
            {
				if(freq_step==10)
					freq_step=100;
				else if(freq_step==100)
					freq_step=1000;
				else if(freq_step==1000)
					freq_step=10;
//				args = freq2args(10);
            }
            reset_all();
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
    DAC_Cmd(DAC_Channel_1, DISABLE);
    DAC_DMACmd(DAC_Channel_1, DISABLE);
    DMA_Cmd(DMA2_Channel3, DISABLE);
    TIM_Cmd(TIM2, DISABLE);
    TIM2_Int_Init(args.arr, args.psc);
    Dac1_Init();
    MYDMA_Config(DMA2_Channel3, (u32) & (DAC->DHR12R1), (u32)data, args.len);
    TIM_Cmd(TIM2, ENABLE);
}

waveArgs freq2args(u32 freq)
{
	waveArgs tmp;
	double b=72000000;
	double delta[1000][3];
	int i,j;
	int label_i,label_j;
	int max_i,max_j;
	if (freq > 245) // len_max
	{
		tmp.arr = 17; // (arr+1)==18,the mininum number.
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
