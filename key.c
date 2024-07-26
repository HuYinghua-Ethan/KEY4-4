/**
* @file		button.c
* @brief	按键
* @version  1.0
* @author   Ethan
* @date     2024.7.11
*/

#include "key.h"
#include "delay.h"

u8 Key_flag=0;  //按键按下标志位，区分按键按下一次的
static u8 Key_Data = 0x00;



/*
遇到的问题：
发现PB3那个IO出现了问题
习惯性以为配置一下IO就可以用了，没有注意到PB3为JTAG共用IO，默认为JTAG状态，需要禁用JTAG才能使用。

通过以下方法解决：
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //必须执行这句话
GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //改变指定管脚的映射完全禁用（JTAG+SW-DP）
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//改变指定管脚的映射，JTAG-DP 禁用 + SW-DP 使能
*/



/**
* @Description	8个按键初始化
* @param	None
* @return   None
*/
static void ButtonLowOutputConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //必须执行这句话
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //改变指定管脚的映射完全禁用（JTAG+SW-DP）
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//改变指定管脚的映射，JTAG-DP 禁用 + SW-DP 使能
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出  
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出  
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出  
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	GPIO_SetBits(GPIOA, GPIO_Pin_11);
	GPIO_SetBits(GPIOA, GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	
}


static void ButtonHighOutputConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //必须执行这句话
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //改变指定管脚的映射完全禁用（JTAG+SW-DP）
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//改变指定管脚的映射，JTAG-DP 禁用 + SW-DP 使能
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入  
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入  
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入  
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}



static void KeyVal_Set(unsigned char n)
{
	Key_Data = 0x00;
	if(n == 0)
	{
		ButtonLowOutputConfig();
		delay_us(500);  //短延时，等待配置完成
		
		if(KEY1 == 1)
		{
//			delay_ms(100);
			Key_Data |= 0x8F;
		}
		else if(KEY2 == 1)
		{
//			delay_ms(100);
			Key_Data |= 0x4F;
		}
		else if(KEY3 == 1)
		{
//			delay_ms(100);
			Key_Data |= 0x2F;
		}
		else if(KEY4 == 1)
		{
//			delay_ms(100);
			Key_Data |= 0x1F;
		}	
		else
		{
			Key_Data |= 0x0F;
		}
					
	}
	else
	{
		ButtonHighOutputConfig();
		delay_us(500);  //短延时，等待配置完成
		
		if(KEY5 == 1)
		{
//			delay_ms(100);
			Key_Data |= 0xF8;
		}
		else if(KEY6 == 1)
		{
//			delay_ms(100);
			Key_Data |= 0xF4;
		}
		else if(KEY7 == 1)
		{
//			delay_ms(100);
			Key_Data |= 0xF2;
		}
		else if(KEY8 == 1)
		{
//			delay_ms(100);
			Key_Data |= 0xF1;
		}	
		else
		{
			Key_Data |= 0xF0;
		}
	}

}

u8 Key_Scan(void)
{
	u8 ButtonVal =16;
	u8 key_x;
	KeyVal_Set(1);
	delay_us(100);  //短延时，等待配置完成
	
	if(Key_Data != 0xF0)
	{
		Key_flag = 1;
		key_x = Key_Data;
		KeyVal_Set(0);
		delay_us(100);  //短延时，等待配置完成

		Key_Data = Key_Data & key_x;
		
		switch(Key_Data)
		{
			case 0x11:
				ButtonVal = back;
				break;
			case 0x12:
				ButtonVal = enter;
				break;
			case 0x14:
				ButtonVal = sub;
				break;
			case 0x18:
				ButtonVal = add;
				break;
			case 0x21:
				ButtonVal = yy;
				break;
			case 0x22:
				ButtonVal = 3;
				break;
			case 0x24:
				ButtonVal = 6;
				break;
			case 0x28:
				ButtonVal = 9;
				break;
			case 0x41:
				ButtonVal = 0;
				break;
			case 0x42:
				ButtonVal = 2;
				break;
			case 0x44:
				ButtonVal = 5;
				break;
			case 0x48:
				ButtonVal = 8;
				break;
			case 0x81:
				ButtonVal = xx;
				break;
			case 0x82:
				ButtonVal = 1;
				break;
			case 0x84:
				ButtonVal = 4;
				break;
			case 0x88:
				ButtonVal = 7;
				break;
				
		}
		KeyVal_Set(0);
		/* 松手检测 */
		while(Key_Data != 0x0F)
		{
			KeyVal_Set(0);
		}
	}
	return ButtonVal;
}



