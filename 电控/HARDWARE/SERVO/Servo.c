#include "Servo.h"

int E5_angle = 1500;
int E6_angle = 1500;
int B8_angle = 1900;
int C9_angle = 440;


void Servo_Init(void)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;           //IO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //��ʱ��	
	TIM_OCInitTypeDef  TIM_OCInitStructure;        //PWM���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM8ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTCʱ��	
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	 
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);


	/*** Initialize timer 1 || ��ʼ����ʱ��1 ***/
	//Set the counter to automatically reload //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1; 
	//Pre-divider //Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Prescaler = 168  - 1; 	
	//Set the clock split: TDTS = Tck_tim //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	//TIM up count mode //TIM���ϼ���ģʽ	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
	//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure); 
	
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
	
	TIM_OC1Init(TIM9, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM9, &TIM_OCInitStructure); 
	//Channel preload enable
	//ͨ��Ԥװ��ʹ��	 
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);
	//-----------�����ʼ��-----------// 
	//Enable timer //ʹ�ܶ�ʱ��
	TIM_Cmd(TIM9, ENABLE); 		 

  //The channel value is initialized to 1500, corresponding to the steering gear zero
	//ͨ��ֵ��ʼ��Ϊ1500���������Ӧֵ
	TIM9->CCR1=E5_angle;
	TIM9->CCR2=E6_angle;
}

void Servo2_Init(void)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;           //IO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //��ʱ��	
	TIM_OCInitTypeDef  TIM_OCInitStructure;        //PWM���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  	//TIM8ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTCʱ��	
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);


	/*** Initialize timer 1 || ��ʼ����ʱ��1 ***/
	//Set the counter to automatically reload //�趨�������Զ���װֵ 
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
	
	TIM_OC4Init(TIM8, &TIM_OCInitStructure); 
	//Channel preload enable
	//ͨ��Ԥװ��ʹ��	 
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	//-----------�����ʼ��-----------// 
	
	//Advanced timer output must be enabled //�߼���ʱ���������ʹ�����	
	TIM_CtrlPWMOutputs(TIM8,ENABLE); 	
	//Enable timer //ʹ�ܶ�ʱ��
	TIM_Cmd(TIM8, ENABLE); 		 

  //The channel value is initialized to 1500, corresponding to the steering gear zero
	//ͨ��ֵ��ʼ��Ϊ1500���������Ӧֵ
	TIM8->CCR4=C9_angle;
}

void Servo3_Init(void)	
{ 
	GPIO_InitTypeDef GPIO_InitStructure;           //IO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //��ʱ��	
	TIM_OCInitTypeDef  TIM_OCInitStructure;        //PWM���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);  	//TIM8ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTCʱ��	
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 	
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM10);


	/*** Initialize timer 1 || ��ʼ����ʱ��1 ***/
	//Set the counter to automatically reload //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1; 
	//Pre-divider //Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Prescaler = 168 - 1; 	
	//Set the clock split: TDTS = Tck_tim //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	//TIM up count mode //TIM���ϼ���ģʽ	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
	//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure); 
	
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
	
	TIM_OC1Init(TIM10, &TIM_OCInitStructure); 
	//Channel preload enable
	//ͨ��Ԥװ��ʹ��	 
	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);
	//-----------�����ʼ��-----------// 
	
	//Advanced timer output must be enabled //�߼���ʱ���������ʹ�����	
	TIM_CtrlPWMOutputs(TIM10,ENABLE); 	
	//Enable timer //ʹ�ܶ�ʱ��
	TIM_Cmd(TIM10, ENABLE); 		 

  //The channel value is initialized to 1500, corresponding to the steering gear zero
	//ͨ��ֵ��ʼ��Ϊ1500���������Ӧֵ
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

