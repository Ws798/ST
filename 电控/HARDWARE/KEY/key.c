#include "key.h"

//按键初始化函数
void KEY_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOA,GPIOE时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //KEY0 对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOE4
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//WK_UP对应引脚PA0
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOA0
 
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY1按下
//2，KEY2按下
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	
	if(mode) key_up=1;  //支持连按
	if(key_up&&(KEY1==0||KEY2==0))
	{
		key_up=0;
		if(KEY1==0) return KEY1_PRES;
		else if(KEY2==0) return KEY2_PRES; 
	}		
	else
	{
		key_up = 1;
	}
 	return 0;// 无按键按下
}




















