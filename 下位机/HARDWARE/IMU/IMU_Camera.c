#include "IMU_Camera.h"

u8 uart3_data;
u8 uart3_packet[100];
u8 uart3_p;
float Roll_Camera,Pitch_Camera,Yaw_Camera;

void uart3_init(u32 bound)
{
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); 
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOD,&GPIO_InitStructure); 

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  USART_Init(USART3, &USART_InitStructure);
	
  USART_Cmd(USART3, ENABLE); 
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}

void Read_Usart3(u8 TYPE_Data);

void USART3_IRQHandler(void) 
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		uart3_data = USART_ReceiveData(USART3);
		uart3_packet[uart3_p++] = uart3_data;
		if(uart3_packet[0] != 0x55) uart3_p=0;
		if(uart3_p >= 11)
		{
			uart3_p = 0;
			Read_Usart3(uart3_packet[1]);
		}
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}
}

void Read_Usart3(u8 TYPE_Data)
{
	static u8 Roll_L, Roll_H, Pitch_L, Pitch_H, Yaw_L, Yaw_H;
	static int16_t Roll_Data, Pitch_Data, Yaw_Data;
	if(TYPE_Data == 0x53)
	{	
		Roll_L  = uart3_packet[2];
		Roll_H  = uart3_packet[3];
		Pitch_L = uart3_packet[4];
		Pitch_H = uart3_packet[5];
		Yaw_L   = uart3_packet[6];
		Yaw_H   = uart3_packet[7];
		Roll_Data =(int16_t)(Roll_H<<8|Roll_L);
		Pitch_Data=(int16_t)(Pitch_H<<8|Pitch_L);
		Yaw_Data  =(int16_t)(Yaw_H<<8|Yaw_L);
		Roll_Camera = ((float)Roll_Data) * 180 / 32768;
		Pitch_Camera = ((float)Pitch_Data) * 180 / 32768;
		Yaw_Camera = ((float)Yaw_Data) * 180 / 32768;
	}
	else {};
}
