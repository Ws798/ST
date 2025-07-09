#include "Motor42.h"

/*��ת����*/
u8 x1_flag_42=1;
u8 y1_flag_42=1;
u8 x2_flag_42=1;
u8 y2_flag_42=1;
u8 flag_57=1;
u8 en_57=0;
u8 dir_57=0;
int dist_57=0;
int ndist_57=0;
u8 balance1_task;
u8 balance2_task;
u8 balance1_time = 6;
u8 balance2_time = 6;
float need_roll2 = -1.76;
float need_pitch2 = 3.02;
float need_roll3 = -3.69;
float need_pitch3 = 0.19;

void TIM14_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);  ///ʹ��TIM2ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStructure);//��ʼ��TIM2
	
	TIM_ITConfig(TIM14,TIM_IT_Update,ENABLE); //����TIM2�����ж�
	TIM_Cmd(TIM14,ENABLE); //ʹ��TIM2
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM8_TRG_COM_TIM14_IRQn; //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//��ʱ��2�жϷ�����
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	u8 f=0;
	if(TIM_GetITStatus(TIM14,TIM_IT_Update)==SET) //����ж�
	{
		if(en_57 || (state_57==1))
		{
			if(state_57 == 1) Dist_57();
			
			if(dir_57 && flag_57) --dist_57;
			else if(!dir_57 && flag_57) ++dist_57;
			
			if(flag_57 == 1) flag_57=0;
			else if(flag_57 == 0) flag_57=1;
			
			Control_57(en_57, dir_57);
		}
		
		if(flag_control!=page_do_ControlM) f=1;
		else f=0;
		
		if(f == 1)
		{
			switch(flag_control)
			{
				case page_do_ControlA: Control_42_x1(1,0);break;
				case page_do_ControlB: Control_42_x1(1,1);break;
				case page_do_ControlC: Control_42_y1(1,1);break;
				case page_do_ControlD: Control_42_y1(1,0);break;
				case page_do_ControlI: Control_42_x2(1,1);break;
				case page_do_ControlJ: Control_42_x2(1,0);break;
				case page_do_ControlK: Control_42_y2(1,1);break;
				case page_do_ControlL: Control_42_y2(1,0);break;
				case page_do_ControlM: f=0;Control_42_x1(0,0);Control_42_x2(0,0);Control_42_y1(0,0);Control_42_y2(0,0);break;
				default: break;
			}
		}
		
		
		
		if(x1_flag_42 == 1) x1_flag_42=0;
		else if(x1_flag_42 == 0) x1_flag_42=1;
		if(y1_flag_42 == 1) y1_flag_42=0;
		else if(y1_flag_42 == 0) y1_flag_42=1;
		if(x2_flag_42 == 1) x2_flag_42=0;
		else if(x2_flag_42 == 0) x2_flag_42=1;
		if(y2_flag_42 == 1) y2_flag_42=0;
		else if(y2_flag_42 == 0) y2_flag_42=1;
		
		if(balance1_task == 1)
		{
			if(Balance1()==1)
			{
				balance1_time--;
				Control_42_x1(0, 0);
				Control_42_y1(0, 0);
				if(balance1_time == 0)
				{
					balance1_task = 0;
					balance1_time = 6;
				}
				
			}
		}
		
		if(balance2_task == 1)
		{
			if(Balance2()==1)
			{
				balance2_time--;
				Control_42_x2(0, 0);
				Control_42_y2(0, 0);
				if(balance2_time == 0)
				{
					balance2_task = 0;
					balance2_time = 6;
				}
			}
		}
	}
	TIM_ClearITPendingBit(TIM14,TIM_IT_Update);  //����жϱ�־λ
}

void Motor42_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//ʹ��GPIOʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
  	
	//GPIO��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��
	
	/*�ƶ��ĸˣ�Ҳ����1*/
	GPIO_ResetBits(GPIOD, GPIO_Pin_0);  //M2-ST
	GPIO_ResetBits(GPIOD, GPIO_Pin_1);  //M1-ST
	GPIO_ResetBits(GPIOD, GPIO_Pin_10); //M2-EN
	GPIO_ResetBits(GPIOD, GPIO_Pin_14); //M1-EN
	GPIO_SetBits(GPIOD, GPIO_Pin_11);   //M2-DIR
	GPIO_SetBits(GPIOD, GPIO_Pin_15);   //M1-DIR
	
	/*�̶��ĸˣ�Ҳ����2*/
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);  //M2-ST
	GPIO_ResetBits(GPIOE, GPIO_Pin_4);  //M1-ST
	GPIO_ResetBits(GPIOB, GPIO_Pin_9); //M2-EN
	GPIO_ResetBits(GPIOC, GPIO_Pin_3); //M1-EN
	GPIO_SetBits(GPIOC, GPIO_Pin_2);   //M2-DIR
	GPIO_SetBits(GPIOC, GPIO_Pin_1);   //M1-DIR
	
	/*57�������*/
	GPIO_ResetBits(GPIOE, GPIO_Pin_0);  //EN
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
	GPIO_ResetBits(GPIOE, GPIO_Pin_2);  //PUL
	GPIO_ResetBits(GPIOE, GPIO_Pin_3);	//DIR
	
	TIM14_Init(42-1, 500-1); //84M
}

void Control_42_x1(u8 en, u8 dir)
{
	if(en == 0) GPIO_ResetBits(GPIOD, GPIO_Pin_10);
	else if(en == 1) GPIO_SetBits(GPIOD, GPIO_Pin_10);
	
	if(dir == 0) GPIO_ResetBits(GPIOD, GPIO_Pin_11);
	else if(dir == 1) GPIO_SetBits(GPIOD, GPIO_Pin_11);
	
	if(x1_flag_42 == 1) {GPIO_SetBits(GPIOD, GPIO_Pin_0);}
	else if(x1_flag_42 == 0) {GPIO_ResetBits(GPIOD, GPIO_Pin_0);}
}

void Control_42_y1(u8 en, u8 dir)
{
	if(en == 0) GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	else if(en == 1) GPIO_SetBits(GPIOD, GPIO_Pin_14);
	
	if(dir == 0) GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	else if(dir == 1) GPIO_SetBits(GPIOD, GPIO_Pin_15);
	
	if(y1_flag_42 == 1) {GPIO_SetBits(GPIOD, GPIO_Pin_1);}
	else if(y1_flag_42 == 0) {GPIO_ResetBits(GPIOD, GPIO_Pin_1);}
}

void Control_42_x2(u8 en, u8 dir)
{
	if(en == 0) GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	else if(en == 1) GPIO_SetBits(GPIOB, GPIO_Pin_9);
	
	if(dir == 0) GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	else if(dir == 1) GPIO_SetBits(GPIOC, GPIO_Pin_2);
	
	if(x2_flag_42 == 1) {GPIO_SetBits(GPIOC, GPIO_Pin_13);}
	else if(x2_flag_42 == 0) {GPIO_ResetBits(GPIOC, GPIO_Pin_13);}
}

void Control_42_y2(u8 en, u8 dir)
{
	if(en == 0) GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	else if(en == 1) GPIO_SetBits(GPIOC, GPIO_Pin_3);
	
	if(dir == 0) GPIO_ResetBits(GPIOC, GPIO_Pin_1);
	else if(dir == 1) GPIO_SetBits(GPIOC, GPIO_Pin_1);
	
	if(y1_flag_42 == 1) {GPIO_SetBits(GPIOE, GPIO_Pin_4);}
	else if(y1_flag_42 == 0) {GPIO_ResetBits(GPIOE, GPIO_Pin_4);}
}

void Control_57(u8 en, u8 dir)
{
	if(en == 1)
	{
		if(flag_57 == 1) {GPIO_SetBits(GPIOE, GPIO_Pin_2);}
		else if(flag_57 == 0) {GPIO_ResetBits(GPIOE, GPIO_Pin_2);}
	}
	else {GPIO_ResetBits(GPIOE, GPIO_Pin_2);}
	
	if(dir == 1) GPIO_SetBits(GPIOE, GPIO_Pin_3);
	else if(dir == 0) GPIO_ResetBits(GPIOE, GPIO_Pin_3);
}

void Dist_57(void)
{
	int mid;
	mid = ndist_57 - dist_57;
	if(mid > 0)
	{
		en_57 = 1;
		dir_57 = 0;
	}
	else if(mid < 0)
	{
		en_57 = 1;
		dir_57 = 1;
	}
	else if(mid == 0)
	{
		en_57 = 0;
		state_57 = 2;
	}
}

u8 Balance1(void)
{
	static u8 r, p;
	static u8 flagr1, flagr2;
	static u8 flagp1, flagp2;
	static u8 value;
	
	if(r == 0)
	{
		if(Roll_2 <= need_roll2) {flagr1=1;Control_42_x1(1, 1);}
		else {flagr2=1;Control_42_x1(1, 0);}
	}
	else if(r)
	{
		Control_42_x1(0, 0);
	}
	
	if(flagr1 && flagr2)
	{
		flagr1 = flagr2 = 0;
		Control_42_x1(0, 0);
		r = 1;
	}
	
	if(p == 0)
	{
		if(Pitch_2 <= need_pitch2) {flagp1=1;Control_42_y1(1, 1);}
		else {flagp2=1;Control_42_y1(1, 0);}
	}
	else if(r)
	{
		Control_42_y1(0, 0);
	}
	
	if(flagp1 && flagp2)
	{
		flagp1 = flagp2 = 0;
		Control_42_y1(0, 0);
		p = 1;
	}
	
	if(r && p)
	{
		r = p = flagr1 = flagr2 = flagp1 = flagp2 = 0;
		value = 1;
	}
	else {value = 0;}
	return value;
}

u8 Balance2(void)
{
	static u8 r, p;
	static u8 flagr1, flagr2;
	static u8 flagp1, flagp2;
	static u8 value;
	
	if(r == 0)
	{
		if(Roll_3 >= need_roll3) {flagr1=1;Control_42_x2(1, 1);}
		else {flagr2=1;Control_42_x2(1, 0);}
	}
	else if(r)
	{
		Control_42_x2(0, 0);
	}
	
	if(flagr1 && flagr2)
	{
		flagr1 = flagr2 = 0;
		Control_42_x2(0, 0);
		r = 1;
	}
	
	if(p == 0)
	{
		if(Pitch_3 <= need_pitch3) {flagp1=1;Control_42_y2(1, 1);}
		else {flagp2=1;Control_42_y2(1, 0);}
	}
	else if(r)
	{
		Control_42_y2(0, 0);
	}
	
	if(flagp1 && flagp2)
	{
		flagp1 = flagp2 = 0;
		Control_42_y2(0, 0);
		p = 1;
	}
	
	if(r && p)
	{
		r = p = flagr1 = flagr2 = flagp1 = flagp2 = 0;
		value = 1;
	}
	else {value = 0;}
	return value;
}


