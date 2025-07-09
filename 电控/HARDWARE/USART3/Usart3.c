#include "usart3.h"	

#if EN_USART3_RX   //���ʹ���˽���

u8 USART3_RxPacket[100];
u8 TYPE = 0;
u8 RxState = 0;
u8 pRxPacket = 0;
u8 RxData;
float Roll_3,Pitch_3,Yaw_3;

//��ʼ��IO ����1 
//bound:������
void uart3_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART3, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART3_RX	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	
}



void USART3_IRQHandler(void)                	//����1�жϷ������
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		RxData = USART_ReceiveData(USART3);
		USART3_RxPacket[pRxPacket++] = RxData;
		if(USART3_RxPacket[0] != 0x55) {pRxPacket = 0;}
		if(pRxPacket >= 11)
		{
			pRxPacket = 0;
			Read_Usart3(USART3_RxPacket[1]);
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
		Roll_L  = USART3_RxPacket[2];
		Roll_H  = USART3_RxPacket[3];
		Pitch_L = USART3_RxPacket[4];
		Pitch_H = USART3_RxPacket[5];
		Yaw_L   = USART3_RxPacket[6];
		Yaw_H   = USART3_RxPacket[7];
		Roll_Data =(int16_t)(Roll_H<<8|Roll_L);
		Pitch_Data=(int16_t)(Pitch_H<<8|Pitch_L);
		Yaw_Data  =(int16_t)(Yaw_H<<8|Yaw_L);
		Roll_3 = ((float)Roll_Data) * 180 / 32768;
		Pitch_3 = ((float)Pitch_Data) * 180 / 32768;
		Yaw_3 = ((float)Yaw_Data) * 180 / 32768;
	}
	else {};
}

//	

////	u8 t;
////	u8 len;	
////	static u8 num[7];

////	if(USART3_RX_STA&0x8000)
////		{  
////			len=USART3_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
////			for(t=0;t<len;t++)
////			{
////				num[t] = USART3_RX_BUF[t]; //�洢����				
////				USART_SendData(USART3, USART3_RX_BUF[t]);         //�򴮿�3��������
////				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
////			}
////			USART3_RX_STA=0;
////			
////		}
////		return num[1];
//}
#endif	


