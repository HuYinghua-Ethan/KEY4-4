#ifndef __KEY_H
#define __KEY_H

#include "sys.h"


#define KEY1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)
#define KEY2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define KEY3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
#define KEY4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define KEY5 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define KEY6 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)
#define KEY7 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)
#define KEY8 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)   



#define xx 10
#define yy 11
#define add 12 
#define sub 13 
#define enter 14 
#define back 15 


u8 Key_Scan(void);

#endif
