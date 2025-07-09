#include "IMU_Notmove.h"

u8 uart4_data;
u8 uart4_packet[100];
u8 uart4_p;
float Roll_Notmove,Pitch_Notmove,Yaw_Notmove;

void uart4_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE); 
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Init(UART4,&USART_InitStructure);   
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
	USART_Cmd(UART4,ENABLE);
}

void Read_Uart4(u8 TYPE_Data);

void UART4_IRQHandler(void)                	//串口5中断服务程序
{
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		uart4_data = USART_ReceiveData(UART4);
		uart4_packet[uart4_p++] = uart4_data;
		if((uart4_p >= 2) && !(uart4_packet[0] == 0x55 && uart4_packet[1] == 0x55)) uart4_p=0;
		if(uart4_p >= 11)
		{
			uart4_p = 0;
			Read_Uart4(uart4_packet[2]);
		}
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	}
}

void Read_Uart4(u8 TYPE_Data)
{
	u8 Roll_L, Roll_H, Pitch_L, Pitch_H, Yaw_L, Yaw_H;
	int16_t Roll_Data, Pitch_Data, Yaw_Data;
	if(TYPE_Data == 0x01)
	{	
		Roll_L  = uart4_packet[4];
		Roll_H  = uart4_packet[5];
		Pitch_L = uart4_packet[6];
		Pitch_H = uart4_packet[7];
		Yaw_L   = uart4_packet[8];
		Yaw_H   = uart4_packet[9];
		Roll_Data =(int16_t)(Roll_H<<8|Roll_L);
		Pitch_Data=(int16_t)(Pitch_H<<8|Pitch_L);
		Yaw_Data  =(int16_t)(Yaw_H<<8|Yaw_L);
		Roll_Notmove = ((float)Roll_Data) * 180 / 32768;
		Pitch_Notmove = ((float)Pitch_Data) * 180 / 32768;
		Yaw_Notmove = ((float)Yaw_Data) * 180 / 32768;
	}
	else {};
}



