#include "Servo.h"

void Servo_Init(void)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;           //IO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //��ʱ��	
	TIM_OCInitTypeDef  TIM_OCInitStructure;        //PWM���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  	//TIM8ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTCʱ��	
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);

	TIM_TimeBaseStructure.TIM_Period = 10000 - 1; 
	//Pre-divider //Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Prescaler = 168 - 1; 	
	//Set the clock split: TDTS = Tck_tim //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	//TIM up count mode //TIM���ϼ���ģʽ	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
	//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 
	
	//-----------�����ʼ��-----------//
	//Select Timer mode :TIM Pulse Width Modulation mode 1
  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	//Compare output enablement
	//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	//Set the pulse value of the capture comparison register to be loaded
	//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_Pulse = 0; 
  //Output polarity :TIM output polarity is higher	
  //�������:TIM����Ƚϼ��Ը�	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;   
	
	//Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM8, &TIM_OCInitStructure); 
	//Channel preload enable
	//ͨ��Ԥװ��ʹ��	 
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	//-----------�����ʼ��-----------// 
	
	//Advanced timer output must be enabled //�߼���ʱ���������ʹ�����	
	TIM_CtrlPWMOutputs(TIM8,ENABLE); 	
	//Enable timer //ʹ�ܶ�ʱ��
	TIM_Cmd(TIM8, ENABLE); 		 

  //The channel value is initialized to 1500, corresponding to the steering gear zero
	//ͨ��ֵ��ʼ��Ϊ1500���������Ӧֵ
	TIM8->CCR1=1500;
	TIM8->CCR2=1500;
	TIM8->CCR3=1500;
	TIM8->CCR4=1500;
}

