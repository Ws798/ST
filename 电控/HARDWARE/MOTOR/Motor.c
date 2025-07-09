#include "Motor.h"

void Move_PWM_Init(uint16_t arr,uint16_t psc)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	  //TIM1时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能PORTE时钟	
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;   //GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure);              //初始化PE口
	
	//Sets the value of the auto-reload register cycle for the next update event load activity
	//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	//Sets the pre-divider value used as the TIMX clock frequency divisor
	//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	//Set the clock split :TDTS = Tck_tim
	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	//Up counting mode 
	//向上计数模式  
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TIMEBASEINITSTRUCT
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

  //Select Timer mode :TIM Pulse Width Modulation mode 1
  //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	//Compare output enablement
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  //Output polarity :TIM output polarity is higher	
  //输出极性:TIM输出比较极性高	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     
	//Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);	
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);	
	//CH1 is pre-loaded and enabled
	//CH1预装载使能	 
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);  //高级定时器输出需要设置这句
  // Enable the TIMX preloaded register on the ARR
  //使能TIMx在ARR上的预装载寄存器	
	TIM_ARRPreloadConfig(TIM1, ENABLE); 
	
	//Enable TIM1
	//使能TIM1
	TIM_Cmd(TIM1, ENABLE);  
} 

void Move_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure1;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure1.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure1);
	
	GPIO_InitTypeDef  GPIO_InitStructur2;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructur2.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructur2.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructur2.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructur2.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructur2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructur2);
	
	GPIO_InitTypeDef  GPIO_InitStructur3;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructur3.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_15;
	GPIO_InitStructur3.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructur3.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructur3.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructur3.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructur3);
}

void Swing_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOF时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	GPIO_ResetBits(GPIOE,GPIO_Pin_7);
}

void Set_Speed(int num, int speed)
{
	if(speed > 0) {speed = 16800 - speed;}
	else if(speed < 0) {speed = -speed - 16800;}

	
	if(speed > 0)
	{
		if(num == 1)      {TIM_SetCompare1(TIM1, speed);M1_H1;M1_L2;}
		else if(num == 2) {TIM_SetCompare2(TIM1, speed);M2_H1;M2_L2;}
		else if(num == 3) {TIM_SetCompare3(TIM1, speed);M3_H1;M3_L2;}
		else if(num == 4) {TIM_SetCompare4(TIM1, speed);M4_H1;M4_L2;}
	}
	else if(speed < 0)
	{
		speed = -speed;
		if(num == 1)      {TIM_SetCompare1(TIM1, speed);M1_H2;M1_L1;}
		else if(num == 2) {TIM_SetCompare2(TIM1, speed);M2_H2;M2_L1;}
		else if(num == 3) {TIM_SetCompare3(TIM1, speed);M3_H2;M3_L1;}	
		else if(num == 4) {TIM_SetCompare4(TIM1, speed);M4_H2;M4_L1;}
	}
	else
	{
		speed = 0;
		if(num == 1)      {TIM_SetCompare1(TIM1, speed);M1_L1;M1_L2;}
		else if(num == 2) {TIM_SetCompare2(TIM1, speed);M2_L1;M2_L2;}
		else if(num == 3) {TIM_SetCompare3(TIM1, speed);M3_L1;M3_L2;}
		else if(num == 4) {TIM_SetCompare4(TIM1, speed);M4_L1;M4_L2;}
	}
}

void Swing_Control(int num, int dir)
{
	if(num == 1)
	{
		if(dir == 1) {GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_15);}
		else if(dir == -1) {GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOB,GPIO_Pin_15);}
		else if(dir == 0) {GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_15);}
	}
	else if(num == 2)
	{
		if(dir == 1) {GPIO_SetBits(GPIOE,GPIO_Pin_7);GPIO_ResetBits(GPIOB,GPIO_Pin_14);}
		else if(dir == -1) {GPIO_ResetBits(GPIOE,GPIO_Pin_7);GPIO_SetBits(GPIOB,GPIO_Pin_14);}
		else if(dir == 0) {GPIO_ResetBits(GPIOE,GPIO_Pin_7);GPIO_ResetBits(GPIOB,GPIO_Pin_14);}
	}
}
