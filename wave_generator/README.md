# wave_generator
A practicing project based on STM32F103ZET6 chip, using the onboard DAC to generate some waves(Sine, Ramp, Trangle, Square).  
## *without_dma* version
This is the initial version. I only use DAC and Timer in this version. The signal is calculated in real time(in the IRQHandler) so it's hard to generate a wave with high frequency.  
## *with_dma* version
This is the completed version. Everytime I change the frequency or the type, the program will pre-calculate the values and storage them in a buffer. Then, the DMA will automatically transfer these values to the DAC register, which will change the output voltage. The DMA is designed to be applied to these occasions and doesn't take up the CPU clocks, so I can generate waves with much higher frequency.
## about the freqency
+ As for the timer, the cycle of timeout(Tout), the clock speed(CLK), the auto reload register(arr), and the prescaler register match this equation: Tout=(arr+1) * (psc+1)/CLK  
+ on STM32F103 chips, the maximum clock speed is 72MHz, which means the minimum Tout is about 27.77ns(seems that the arr must be 1 or higher)  
+ Assume that your wave consists of *LEN* points, it will take (LEN * Tout) to output a cycle of your wave. Then, these parameters match this equation:T=LEN * (arr+1) * (psc+1)/CLK, so theoretically, the the frequency of your wave is (CLK/(LEN * (arr+1) * (psc+1)))
+ However, it seems that the ((arr+1) * (psc+1)) should equal to or be higher than 18 otherwise the internel latency will affect.
+ STM32F4 chips might have better performance.