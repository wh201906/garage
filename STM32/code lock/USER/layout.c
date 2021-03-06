#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "OLED_I2C.h"
#include "sensor.h"
#include "24cxx.h"
#include "bitband.h"
#include "layout.h"
#include "math.h"
#include "stdio.h"

extern u8 PassExist;
extern u8 Pswd[PASSLEN];
char list[20][20] = {"Set/Change Password", "Display Settings", "Measure", "LED", "Beep", "Solve", "Test1", "Test2", "Test3"};

void ShowLED(u8 st)
{
    if (st)
    {
        PEout(5) = 0;
        delay_ms(10);
        PEout(5) = 1;
    }
    else
    {
        PBout(5) = 0;
        delay_ms(10);
        PBout(5) = 1;
    }
}

void Menu_Refresh(u8 start, u8 curr)
{
    int i;
    for (i = start - 1; i - start < 4; i++)
    {
        if (i == curr - 1)
        {
            OLED_ShowRevStr(0, 3 + i - start, "                     ", 1);
            OLED_ShowRevChar(0, 3 + i - start, i + '1', 1);
            OLED_ShowRevChar(6, 3 + i - start, '.', 1);
            OLED_ShowRevStr(12, 3 + i - start, list[i], 1);
        }
        else
        {
            OLED_ShowStr(0, 3 + i - start, "                     ", 1);
            OLED_ShowChar(0, 3 + i - start, i + '1', 1);
            OLED_ShowChar(6, 3 + i - start, '.', 1);
            OLED_ShowStr(12, 3 + i - start, list[i], 1);
        }
    }
}

double s2f(int len, char str[])
{
    double res = 0, tmp;
    int i, j, start = 0;
    if (str[0] == '-')
        start = 1;
    for (i = start; i < len && str[i] != '.'; i++)
        ;
    tmp = 1;
    for (j = i - 1; j >= start; j--)
    {
        res += tmp * (str[j] - '0');
        tmp *= 10;
    }
    if (str[i] == '.')
    {
        tmp = 0.1;
        for (j = i + 1; j < len; j++)
        {
            res += tmp * (str[j] - '0');
            tmp /= 10.0;
        }
    }
    if (str[0] == '-')
        res = -res;
    return res;
}

int fequal(double x1,double x2)
{
    if(x1>x2)
        return (x1-x2<0.0000001);
    else
        return (x2-x1<0.0000001);
}

int solve_input(double* dest)
{
    int len;
    while (1)
    {
        while (!(USART_RX_STA & 0x8000) && PEin(4))
            delay_ms(100);
        if (!PEin(4))
            return 0;
        else
        {
            len = USART_RX_STA & 0x3f;
            USART_RX_STA = 0;
            sscanf(USART_RX_BUF,"%lf",dest);
            sprintf(USART_RX_BUF,"%.3lf",*dest);
            //*dest=s2f(len,USART_RX_BUF);
            OLED_ShowStr(8*6,5,USART_RX_BUF,1);
            for(len=0; len<USART_REC_LEN; len++)
            {
                USART_RX_BUF[len]=0;
            }
            delay_ms(2000);
            return 1;
        }
    }
}
void fakePWM(volatile unsigned long  * out,int ratio)
{
    int res=256-ratio,i;
    *out=1;
    for(i=0; i<ratio; i++)
        ;
    *out=0;
    for(i=0; i<res; i++)
        ;
}
void Layout_init()
{
    GPIO_InitTypeDef git;
    IIC_Init();
    uart_init(9600);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);
    git.GPIO_Pin = GPIO_Pin_12;
    git.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &git);
    git.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_Init(GPIOE, &git);
    git.GPIO_Pin = GPIO_Pin_0;
    git.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &git);

    git.GPIO_Pin = GPIO_Pin_5;
    git.GPIO_Mode = GPIO_Mode_Out_PP;
    git.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &git);
    GPIO_Init(GPIOE, &git);
    git.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOB, &git);
    PBout(5) = 1;
    PEout(5) = 1;
    PBout(8) = 0;

    PassExist = AT24CXX_ReadOneByte(0);
    AT24CXX_Read(1, Pswd, PASSLEN);

    RevState = AT24CXX_ReadOneByte(PASSLEN + 7);
    brightness = AT24CXX_ReadOneByte(PASSLEN + 9);
    OLED_Init();
}

int Layout_unlock()
{
    if (AT24CXX_ReadOneByte(PASSLEN + 5))
        return 0;
    u8 count = 3, cycle, len;
    OLED_CLS();
    delay_ms(2);
    OLED_ShowStr(0, 0, "Locked System!", 2);
    OLED_ShowStr(0, 3, "Plz input the passwd:", 1);
    OLED_ShowChar(120, 0, '3', 1);
    for (count = 3; count > 0; count--)
    {
        for(cycle=0; cycle<USART_REC_LEN; cycle++)
        {
            USART_RX_BUF[cycle]=0;
        }
        while (!(USART_RX_STA & 0x8000))
            ;
        len = USART_RX_STA & 0x3f;
        USART_RX_STA = 0;
        for (cycle = 0; cycle < len; cycle++)
            if (Pswd[cycle] != USART_RX_BUF[cycle])
                break;
        if (cycle >= len && PassExist == len)
        {
            OLED_ShowStr(0, 4, "Passed!", 1);
            delay_ms(3000);
            return 1;
        }
        else
        {
            OLED_ShowChar(120, 0, count - 1 + '0', 1);
            for (cycle = 0; cycle < 3; cycle++)
            {
                OLED_ShowStr(0, 4, "Wrong!", 1);
                delay_ms(500);
                OLED_ShowStr(0, 4, "      ", 1);
                delay_ms(500);
            }
        }
        delay_ms(200);
    }
    AT24CXX_WriteOneByte(PASSLEN + 5, 1);
    return 0;
}

void Layout_reset()
{
    u8 count = 0;
    OLED_CLS();
    OLED_ShowStr(0, 0, "Totally Locked!", 2);
    OLED_ShowStr(0, 3, "You can't unlock it b", 1);
    OLED_ShowStr(0, 4, "y any means now.", 1);
    while (1)
    {
        if (!PAin(0) && PBin(12) && PEin(2) && !PEin(3) && PEin(4))
        {
            ShowLED(1);
            delay_ms(1000);
            for (count = 0; (PAin(0) || !PBin(12) || PEin(2) || !PEin(3) || PEin(4)) && count < 5; count++)
                delay_ms(1000);
            if (count >= 5)
            {
                ShowLED(0);
            }
            else
            {
                ShowLED(1);
                delay_ms(1000);
                for (count = 0; (PAin(0) || PBin(12) || !PEin(2) || !PEin(3) || !PEin(4)) && count < 5; count++)
                    delay_ms(1000);
                if (count >= 5)
                {
                    ShowLED(0);
                }
                else
                {
                    ShowLED(1);
                    delay_ms(1000);
                    for (count = 0; (!PAin(0) || !PBin(12) || !PEin(2) || PEin(3) || !PEin(4)) && count < 5; count++)
                        delay_ms(1000);
                    if (count >= 5)
                    {
                        ShowLED(0);
                    }
                    else
                    {
                        ShowLED(1);
                        OLED_CLS();
                        OLED_ShowStr(0, 0, "Storage wiping", 1);
                        delay_ms(1000);
                        OLED_ShowChar(14 * 6, 0, '.', 1);
                        delay_ms(1000);
                        OLED_ShowChar(15 * 6, 0, '.', 1);
                        delay_ms(1000);
                        OLED_ShowChar(16 * 6, 0, '.', 1);
                        delay_ms(1000);
                        AT24CXX_WriteOneByte(0, 0);
                        AT24CXX_WriteOneByte(PASSLEN + 5, 0);
                        OLED_ShowStr(0, 1, "Storage wiped.", 1);
                        delay_ms(5000);
                        NVIC_SystemReset();
                    }
                }
            }
        }
    }
}

int Layout_main()
{
    u8 cycle;
    OLED_CLS();
    delay_ms(2);
    OLED_ShowStr(4*8, 0, "Welcome!", 2);
    OLED_ShowStr(0, 3, "Passwd:", 1);
    PassExist = AT24CXX_ReadOneByte(0);
    if (!PassExist)
        OLED_ShowStr(7 * 6, 3, "<none>", 1);
    else
    {
        AT24CXX_Read(1, Pswd, PassExist);
        Pswd[PassExist] = 0;
        OLED_ShowStr(7 * 6, 3, Pswd, 1);
    }
    OLED_ShowStr(0, 7, "KEY0:Menu   KEY1:Lock", 1);
    while (1)
    {
        if (!PEin(4))
            return 0;
        else if (!PEin(3))
        {
            if (PassExist)
                return 1;
            else
            {
                for (cycle = 0; cycle < 3; cycle++)
                {
                    OLED_ShowStr(0, 4, "Plz set passwd first.", 1);
                    delay_ms(500);
                    OLED_ShowStr(0, 4, "                     ", 1);
                    delay_ms(500);
                    OLED_SetBrightness(20);
                }
            }
        }
    }
}

int Layout_menu(void)
{
    u8 start = 1, curr = 1;
    OLED_CLS();
    OLED_ShowStr(6*8, 0, "Menu", 2);
    Menu_Refresh(1, 1);
    OLED_ShowStr(0, 7, "KEY0:back", 1);
    while (1)
    {
        if (!PEin(4))
            return 0;
        else if (!PEin(2))
            return curr;
        else if (!PEin(3))
        {
            if (start == 1)
            {
                if (curr > 1)
                    curr--;
                else
                {
                    start = MENULEN - 4;
                    curr = MENULEN;
                }
            }
            else
            {
                if (start >= curr)
                    start--;
                curr--;
            }
            Menu_Refresh(start, curr);
        }
        else if (PAin(0))
        {
            if (start == MENULEN - 4)
            {
                if (curr < MENULEN)
                    curr++;
                else
                {
                    start = 1;
                    curr = 1;
                }
            }
            else
            {
                if (start <= curr - 4)
                    start++;
                curr++;
            }
            Menu_Refresh(start, curr);
        }
        delay_ms(20);
    }
}

void Layout_set(void)
{
    u8 cycle, len;
    OLED_CLS();
    OLED_ShowStr(0, 0, "Password", 2);
    OLED_ShowStr(0, 3, "Input the new passwd:", 1);
    OLED_ShowStr(0, 7, "KEY0:back  KEY1:Clear", 1);
    while (1)
    {
        while (!(USART_RX_STA & 0x8000) && PEin(4) && PEin(3))
            delay_ms(100);
        if (!PEin(4))
            return;
        else if (!PEin(3))
        {
            PassExist = 0;
            AT24CXX_WriteOneByte(0, 0);
            OLED_ShowStr(0, 4, "Passwd cleared.", 1);
        }
        else
        {
            len = USART_RX_STA & 0x3f;
            USART_RX_STA = 0;
            if (len >= 4 && len <= PASSLEN - 1)
            {
                PassExist = len;
                for (cycle = 0; cycle < len; cycle++)
                    Pswd[cycle] = USART_RX_BUF[cycle];
                AT24CXX_WriteOneByte(0, len);
                AT24CXX_Write(1, Pswd, len);
                OLED_ShowStr(0, 4, "Passwd has been set.", 1);
            }
            else
            {
                for (cycle = 0; cycle < 3; cycle++)
                {
                    OLED_ShowStr(0, 4, "Invalid length!", 1);
                    delay_ms(500);
                    OLED_ShowStr(0, 4, "               ", 1);
                    delay_ms(500);
                }
            }
            for(cycle=0; cycle<USART_REC_LEN; cycle++)
            {
                USART_RX_BUF[cycle]=0;
            }
        }
    }
}

void Layout_measure(void)
{
    u8 res, x;
    int humid, humif, tempd, tempf;
    OLED_CLS();
    OLED_ShowStr(0, 0, "Measure", 2);
    OLED_ShowStr(0, 7, "KEY0:back   KEY1:hold", 1);
    OLED_ShowStr(0, 3, "Initializating", 1);
    Sensor_Init();
    for (x = 1; x < 80; x++)
    {
        delay_ms(50);
        if (x % 20 == 0)
            OLED_ShowChar((13 + x / 20) * 6, 3, '.', 1);
        if (!PEin(4))
            return;
    }

    while (1)
    {
        res = Sensor_Measure(&tempd, &tempf, &humid, &humif);
        if (res != 2)
        {
            OLED_ShowStr(0, 3, "Temperature:     ", 1);
            OLED_ShowStr(0, 4, "Humidity:     ", 1);
            if (res == 0)
            {
                x = 12 * 6;
                x += OLED_ShowInt(x, 3, tempd, 1) * 6;
                OLED_ShowChar(x, 3, '.', 1);
                x += 6;
                x += OLED_ShowInt(x, 3, tempf, 1) * 6;
                x = 9 * 6;
                x += OLED_ShowInt(x, 4, humid, 1) * 6;
                OLED_ShowChar(x, 4, '.', 1);
                x += 6;
                x += OLED_ShowInt(x, 4, humif, 1) * 6;
                OLED_ShowChar(x, 4, '%', 1);
            }
            else
            {
                OLED_ShowStr(12 * 6, 3, "error", 1);
                OLED_ShowStr(9 * 6, 4, "error", 1);
            }
        }
        else
        {
            OLED_ShowStr(0, 3, "Not connected.   ", 1);
            OLED_ShowStr(0, 4, "              ", 1);
        }
        for (x = 0; x < 115; x++)
        {
            while (!PEin(3))
                delay_ms(10);
            delay_ms(10);
            if (!PEin(4))
                return;
        }
    }
}

void Layout_display(void)
{
    u8 x;
    OLED_CLS();
    OLED_ShowStr(0, 0, "Display", 2);
    OLED_ShowStr(0, 7, "KEY0:back    KEY2:rev", 1);
    OLED_ShowStr(0, 3, "Brightness:", 1);
    for (x = 0; x < brightness / 2 - 1; x += 2)
    {
        OLED_SetPos(x, 4);
        WriteDat(0xf8);
        WriteDat(0xf8);
    }
    while (1)
    {
        if (!PEin(4))
        {
            if (RevState != AT24CXX_ReadOneByte(PASSLEN + 7))
                AT24CXX_WriteOneByte(PASSLEN + 7, RevState);
            if (brightness != AT24CXX_ReadOneByte(PASSLEN + 9))
                AT24CXX_WriteOneByte(PASSLEN + 9, brightness);
            return;
        }
        else if (!PEin(2))
        {
            OLED_Reverse();
        }
        else if (!PEin(3))
        {
            if (brightness < 0xff)
            {
                brightness += 4;
                OLED_SetBrightness(brightness);
                OLED_SetPos(x, 4);
                WriteDat(0xf8);
                WriteDat(0xf8);
                x += 2;
            }
        }
        else if (PAin(0))
        {
            if (brightness > 0xf)
            {
                brightness -= 4;
                OLED_SetBrightness(brightness);
                x -= 2;
                OLED_SetPos(x, 4);
                WriteDat(0x00);
                WriteDat(0x00);
            }
        }
        delay_ms(200);
    }
}

void Layout_Test(int id)
{
    u8 x;
    OLED_CLS();
    OLED_ShowStr(0, 0, list[id-1], 2);
    OLED_ShowStr(0, 7, "KEY0:back", 1);
    OLED_ShowStr(0, 2, "You entered this page", 1);
    OLED_ShowStr(0, 3, "by item #", 1);
    OLED_ShowInt(9 * 6, 3, id, 1);
    OLED_ShowStr(0, 4, "It's under constructi", 1);
    OLED_ShowStr(0, 5, "n now.", 1);
    while (1)
    {
        if (!PEin(4))
            return;
    }
}

void Layout_solve(void)
{
    int len, cycle;
    double a, b, c, x1, x2, delta;
    OLED_CLS();
    OLED_ShowStr(0, 0, "Solve", 2);
    OLED_ShowStr(0, 7, "KEY0:back    KEY1:new", 1);
    OLED_ShowStr(0, 3, "The equration is like", 1);
    OLED_ShowStr(0, 4, "Ax^2+Bx+C=0", 1);
    while (1)
    {
        OLED_ShowStr(0, 6, "                    ", 1);
        OLED_ShowStr(0, 5, "Input A:            ", 1);
        if(!solve_input(&a))
            return;
        OLED_ShowStr(0, 5, "Input B:            ", 1);
        if(!solve_input(&b))
            return;
        OLED_ShowStr(0, 5, "Input C:            ", 1);
        if(!solve_input(&c))
            return;
        if (fequal(a, 0))
        {
            x1 = -c / b;
            OLED_ShowStr(0, 5, "X:                  ", 1);
            OLED_ShowFloat(2 * 6, 5, x1, 1);
        }
        else
        {
            delta = b * b - 4 * a * c;
            if (fequal(delta, 0))
            {
                x1 = -b / (2 * a);
                OLED_ShowStr(0, 5, "X:                  ", 1);
                OLED_ShowFloat(2 * 6, 5, x1, 1);
            }
            else if (delta < 0)
            {
                OLED_ShowStr(0, 5, "No Solution.        ", 1);
            }
            else
            {
                delta = sqrt(delta);
                x1 = (delta - b) / (2 * a);
                x2 = -(delta + b) / (2 * a);
                OLED_ShowStr(0, 5, "X1:                 ", 1);
                OLED_ShowFloat(3 * 6, 5, x1, 1);
                OLED_ShowStr(0, 6, "X2:                 ", 1);
                OLED_ShowFloat(3 * 6, 6, x2, 1);
            }
        }
        while(PEin(3))
            if (!PEin(4))
                return;
    }
}

void Layout_beep(void)
{
    u8 x = 255;
    int i;
    OLED_CLS();
    OLED_ShowStr(0, 0, "Beep", 2);
    OLED_ShowStr(0, 7, "KEY0:back", 1);
    while (1)
    {
        if (!PEin(3))
        {
            if (x < 255)
                x += 1;
        }
        else if (PAin(0))
        {
            if (x > 0)
                x -= 1;
        }
        else if (!PEin(4))
        {
            PBout(8) = 0;
            return;
        }
        for (i = 0; i < 5000; i++)
            fakePWM(&PBout(8), x);
    }
}
void Layout_led(void)
{
    u8 x = 0, mode = 0,fac=1;
    int i,j;
    OLED_CLS();
    OLED_ShowStr(0, 0, "LED", 2);
    OLED_ShowChar(120, 0, '1', 1);
    OLED_ShowStr(0, 7, "KEY0:back   KEY2:mode", 1);
    while (1)
    {
        if (!PEin(3))
        {
            if (x > 0)
                x -= 10;
        }
        else if (PAin(0))
        {
            if (x < 250)
                x += 10;
        }
        else if (!PEin(4))
        {
            PBout(5) = 1;
            PEout(5) = 1;
            return;
        }
        else if (!PEin(2))
        {
            x = 0;
            fac=1;
            PBout(5) = 1;
            PEout(5) = 1;
            mode++;
            mode%=6;
            OLED_ShowChar(120, 0, mode + '1', 1);
        }
        switch (mode)
        {
        case 0:
            for (i = 0; i < 8000; i++)
                fakePWM(&PBout(5), x);
            break;
        case 1:
            for (i = 0; i < 8000; i++)
                fakePWM(&PEout(5), x);
            break;
        case 2:
            for (i = 0; i < 12000; i++)
            {
                fakePWM(&PBout(5), x);
                fakePWM(&PEout(5), x);
            }
            break;
        case 3:
            if(fac)
            {
                for (i = 0; i < 256; i++)
                {
                    for (j = 0; j < 80; j++)
                        fakePWM(&PBout(5), i);
                }
            }
            else
            {
                for (i = 255; i >= 0; i--)
                {
                    for (j = 0; j < 80; j++)
                        fakePWM(&PBout(5), i);
                }
            }
            fac=!fac;
            break;
        case 4:
            if(fac)
            {
                for (i = 0; i < 256; i++)
                {
                    for (j = 0; j < 80; j++)
                        fakePWM(&PEout(5), i);
                }
            }
            else
            {
                for (i = 255; i >= 0; i--)
                {
                    for (j = 0; j < 80; j++)
                        fakePWM(&PEout(5), i);
                }
            }
            fac=!fac;
            break;
        case 5:
            if(fac)
            {
                PBout(5)=1;
                PEout(5)=0;
                delay_ms(500);
                PEout(5)=1;
                delay_ms(500);
            }
            else
            {
                PBout(5)=0;
                PEout(5)=1;
                delay_ms(500);
                PBout(5)=1;
                delay_ms(500);
            }
            fac=!fac;
            break;
        }

    }
}
