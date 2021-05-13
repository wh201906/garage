#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

#define SDA_IN()  {GPIOB->MODER&=0XFFFF0FFF;GPIOB->MODER|=(u32)1<<12;}
#define SDA_OUT() {GPIOB->MODER&=0XFFFF0FFF;GPIOB->MODER|=(u32)5<<12;}


#define IIC_SCL    PBout(6)
#define IIC_SDA    PBout(7)
#define READ_SDA   PBin(7) 


void IIC_Init(void);		 
void IIC_Start(void);			
void IIC_Stop(void);	  		
void IIC_Send_Byte(u8 txd);		
u8 IIC_Read_Byte(unsigned char ack);
u8 IIC_Wait_Ack(void); 			
void IIC_Ack(void);				
void IIC_NAck(void);	

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















