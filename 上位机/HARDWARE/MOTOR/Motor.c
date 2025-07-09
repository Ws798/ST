#include "Motor.h"
/*
点击驱动
移动，前摆臂，后摆臂
*/
void TIM3_Init(void)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;           //IO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定时器	
	TIM_OCInitTypeDef  TIM_OCInitStructure;        //PWM输出
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTA时钟	
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	 
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	 
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);


	/*** Initialize timer 1 || 初始化定时器1 ***/
	//Set the counter to automatically reload //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Period = 100 - 1; 
	//Pre-divider //预分频器 
	TIM_TimeBaseStructure.TIM_Prescaler = 42  - 1; 	
	//Set the clock split: TDTS = Tck_tim //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	//TIM up count mode //TIM向上计数模式	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	//-----------舵机初始化-----------//
	//Select Timer mode :TIM Pulse Width Modulation mode 1
  //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	//Compare output enablement
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	//Set the pulse value of the capture comparison register to be loaded
	//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_Pulse = 0; 
  //Output polarity :TIM output polarity is higher	
  //输出极性:TIM输出比较极性高	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;   
	
	//Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
	//Channel preload enable
	//通道预装载使能	 
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	//Enable timer //使能定时器
	TIM_Cmd(TIM3, ENABLE); 		 

	TIM3->CCR1=0;
	TIM3->CCR2=0;
	TIM3->CCR3=0;
	TIM3->CCR4=0;
}

void TIM4_Init(void)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;           //IO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定时器	
	TIM_OCInitTypeDef  TIM_OCInitStructure;        //PWM输出
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTA时钟	
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	 
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);


	/*** Initialize timer 1 || 初始化定时器1 ***/
	//Set the counter to automatically reload //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Period = 100 - 1; 
	//Pre-divider //预分频器 
	TIM_TimeBaseStructure.TIM_Prescaler = 42  - 1; 	
	//Set the clock split: TDTS = Tck_tim //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	//TIM up count mode //TIM向上计数模式	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
	//-----------舵机初始化-----------//
	//Select Timer mode :TIM Pulse Width Modulation mode 1
  //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	//Compare output enablement
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	//Set the pulse value of the capture comparison register to be loaded
	//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_Pulse = 0; 
  //Output polarity :TIM output polarity is higher	
  //输出极性:TIM输出比较极性高	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;   
	
	//Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); 
	//Channel preload enable
	//通道预装载使能	 
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	//Enable timer //使能定时器
	TIM_Cmd(TIM4, ENABLE); 		 

	TIM4->CCR1=0;
	TIM4->CCR2=0;
	TIM4->CCR3=0;
	TIM4->CCR4=0;
}

void Motor_Init(void)
{
	TIM3_Init();
	TIM4_Init();	
}

void Set(void) //调试
{
	TIM_SetCompare1(TIM3, 50); 
	TIM_SetCompare2(TIM3, 50);
	TIM_SetCompare3(TIM3, 50);
	TIM_SetCompare4(TIM3, 50);
	TIM_SetCompare1(TIM4, 50);
	TIM_SetCompare2(TIM4, 50);
	TIM_SetCompare3(TIM4, 50);
	TIM_SetCompare4(TIM4, 50);
}

void Move(int s1, int s2) //s1左轮速度，s2右轮速度
{
	if(s1 > 0) //左轮
	{
		TIM_SetCompare2(TIM3, 0);
		TIM_SetCompare1(TIM3, s1); 
	}		
	else if(s1 < 0) 
	{
		TIM_SetCompare1(TIM3, 0); 
		TIM_SetCompare2(TIM3, -s1);
	}		
	else if(s1 == 0) 
	{
		TIM_SetCompare1(TIM3, 0);
		TIM_SetCompare2(TIM3, 0);
	}
	
	if(s2 > 0) //右轮 
	{
		TIM_SetCompare4(TIM3, 0);
		TIM_SetCompare3(TIM3, s2); 
	}		
	else if(s2 < 0) 
	{
		TIM_SetCompare3(TIM3, 0); 
		TIM_SetCompare4(TIM3, -s2);
	}		
	else if(s2 == 0) 
	{
		TIM_SetCompare3(TIM3, 0);
		TIM_SetCompare4(TIM3, 0);
	}
}

void Ahead(u8 mode) //前摆臂
{
	if(mode == Turn_Stop)
	{
		TIM_SetCompare1(TIM4, 0);
		TIM_SetCompare2(TIM4, 0);
	}
	else if(mode == Turn_Ahead)
	{
		TIM_SetCompare2(TIM4, 0);
		TIM_SetCompare1(TIM4, Ahead_Speed);
	}
	else if(mode == Turn_back)
	{
		TIM_SetCompare1(TIM4, 0);
		TIM_SetCompare2(TIM4, Ahead_Speed);
	}
}

void Back(u8 mode) //后三角
{
	if(mode == Turn_Stop)
	{
		TIM_SetCompare3(TIM4, 0);
		TIM_SetCompare4(TIM4, 0);
	}
	else if(mode == Turn_Ahead)
	{
		TIM_SetCompare4(TIM4, 0);
		TIM_SetCompare3(TIM4, Back_Speed);
	}
	else if(mode == Turn_back)
	{
		TIM_SetCompare3(TIM4, 0);
		TIM_SetCompare4(TIM4, Back_Speed);
	}
}
