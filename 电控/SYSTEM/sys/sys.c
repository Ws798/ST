#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//系统时钟初始化	
//包括时钟设置/中断管理/GPIO设置等
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//********************************************************************************
//修改说明
//无
//////////////////////////////////////////////////////////////////////////////////  


//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//开启所有中断
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}


void System_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);		//延时初始化 
	uart_init(9600);	//串口初始化波特率为115200
	uart2_init(115200);
	uart3_init(115200);
	uart4_init(9600);
	uart5_init(115200);
	TIM2_Init(100-1, 840-1); //频率为1000
	LED_Init();
	
	/************电机初始化************/
	Move_PWM_Init(16799, 0);  //电机PWM初始化
	Move_Init();							//移动引脚初始化
	Swing_Init();
	Encoder_Init();
	Motor42_Init();
	/************电机初始化************/
	
	/***********ADC电压检测***********/
//	Adc_Init();
	/***********ADC电压检测***********/
	
	/***********OLED初始化***********/
	OLED_Init();
	/***********OLED初始化***********/
	
	/***********PS2初始化***********/
	PS2_Init();
	/***********PS2初始化***********/
	
	/***********按键初始化***********/
	KEY_Init();
	/***********按键初始化***********/
	
	Servo_Init();
	Servo2_Init();
	Servo3_Init();
	
	dis[0] = 0;
	dis[1] = 5000;
	dis[2] = 10000;
	dis[3] = 15000;
	dis[4] = 20000;
	dis[5] = 25000;
	
	ang[0] = 2540;
	ang[1] = 2480;
	ang[2] = 2400;
	ang[3] = 2320;
	ang[4] = 2280;
	ang[5] = 2220;
	
	Toapp[0] = 123;
}













