#include "Servo.h"

int E5_angle = 1500;
int E6_angle = 1500;
int B8_angle = 1900;
int C9_angle = 440;


void Servo_Init(void)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;           //IO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定时器	
	TIM_OCInitTypeDef  TIM_OCInitStructure;        //PWM输出
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM8时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能PORTC时钟	
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	 
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);


	/*** Initialize timer 1 || 初始化定时器1 ***/
	//Set the counter to automatically reload //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1; 
	//Pre-divider //预分频器 
	TIM_TimeBaseStructure.TIM_Prescaler = 168  - 1; 	
	//Set the clock split: TDTS = Tck_tim //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	//TIM up count mode //TIM向上计数模式	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure); 
	
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
	
	TIM_OC1Init(TIM9, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM9, &TIM_OCInitStructure); 
	//Channel preload enable
	//通道预装载使能	 
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);
	//-----------舵机初始化-----------// 
	//Enable timer //使能定时器
	TIM_Cmd(TIM9, ENABLE); 		 

  //The channel value is initialized to 1500, corresponding to the steering gear zero
	//通道值初始化为1500，舵机零点对应值
	TIM9->CCR1=E5_angle;
	TIM9->CCR2=E6_angle;
}

void Servo2_Init(void)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;           //IO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定时器	
	TIM_OCInitTypeDef  TIM_OCInitStructure;        //PWM输出
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  	//TIM8时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTC时钟	
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);


	/*** Initialize timer 1 || 初始化定时器1 ***/
	//Set the counter to automatically reload //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1; 
	//Pre-divider //预分频器 
	TIM_TimeBaseStructure.TIM_Prescaler = 168 - 1; 	
	//Set the clock split: TDTS = Tck_tim //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	//TIM up count mode //TIM向上计数模式	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 
	
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
	
	TIM_OC4Init(TIM8, &TIM_OCInitStructure); 
	//Channel preload enable
	//通道预装载使能	 
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	//-----------舵机初始化-----------// 
	
	//Advanced timer output must be enabled //高级定时器输出必须使能这句	
	TIM_CtrlPWMOutputs(TIM8,ENABLE); 	
	//Enable timer //使能定时器
	TIM_Cmd(TIM8, ENABLE); 		 

  //The channel value is initialized to 1500, corresponding to the steering gear zero
	//通道值初始化为1500，舵机零点对应值
	TIM8->CCR4=C9_angle;
}

void Servo3_Init(void)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;           //IO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定时器	
	TIM_OCInitTypeDef  TIM_OCInitStructure;        //PWM输出
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);  	//TIM8时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTC时钟	
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM10);


	/*** Initialize timer 1 || 初始化定时器1 ***/
	//Set the counter to automatically reload //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1; 
	//Pre-divider //预分频器 
	TIM_TimeBaseStructure.TIM_Prescaler = 168 - 1; 	
	//Set the clock split: TDTS = Tck_tim //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	//TIM up count mode //TIM向上计数模式	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure); 
	
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
	
	TIM_OC1Init(TIM10, &TIM_OCInitStructure); 
	//Channel preload enable
	//通道预装载使能	 
	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);
	//-----------舵机初始化-----------// 
	
	//Advanced timer output must be enabled //高级定时器输出必须使能这句	
	TIM_CtrlPWMOutputs(TIM10,ENABLE); 	
	//Enable timer //使能定时器
	TIM_Cmd(TIM10, ENABLE); 		 

  //The channel value is initialized to 1500, corresponding to the steering gear zero
	//通道值初始化为1500，舵机零点对应值
	TIM10->CCR1=B8_angle;
}

void Set_Servo_E5(int pwm)
{
	TIM_SetCompare1(TIM9, pwm);
}

void Set_Servo_E6(int pwm)
{
	TIM_SetCompare2(TIM9, pwm);
}

void Set_Servo_C9(int pwm)
{
	TIM_SetCompare4(TIM8, pwm);
}

void Set_Servo_B8(int pwm)
{
	TIM_SetCompare1(TIM10, pwm);
}

