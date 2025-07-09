#include "IMU_Move.h"

u8 uart5_data;
u8 uart5_packet[100];
u8 uart5_p;
float Roll_Move,Pitch_Move,Yaw_Move;

//串口5
void uart5_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure1;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE); 
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure1.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure1);
    
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Init(UART5,&USART_InitStructure);   
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	USART_Cmd(UART5,ENABLE);
}

void Read_Uart5(u8 TYPE_Data);

void UART5_IRQHandler(void)                	//串口5中断服务程序
{
	if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{
		uart5_data = USART_ReceiveData(UART5);
		uart5_packet[uart5_p++] = uart5_data;
		if((uart5_p >= 2) && !(uart5_packet[0] == 0x55 && uart5_packet[1] == 0x55)) uart5_p=0;
		if(uart5_p >= 11)
		{
			uart5_p = 0;
			Read_Uart5(uart5_packet[2]);
		}
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
	}
}

void Read_Uart5(u8 TYPE_Data)
{
	u8 Roll_L, Roll_H, Pitch_L, Pitch_H, Yaw_L, Yaw_H;
	int16_t Roll_Data, Pitch_Data, Yaw_Data;
	if(TYPE_Data == 0x01)
	{	
		Roll_L  = uart5_packet[4];
		Roll_H  = uart5_packet[5];
		Pitch_L = uart5_packet[6];
		Pitch_H = uart5_packet[7];
		Yaw_L   = uart5_packet[8];
		Yaw_H   = uart5_packet[9];
		Roll_Data =(int16_t)(Roll_H<<8|Roll_L);
		Pitch_Data=(int16_t)(Pitch_H<<8|Pitch_L);
		Yaw_Data  =(int16_t)(Yaw_H<<8|Yaw_L);
		Roll_Move = ((float)Roll_Data) * 180 / 32768;
		Pitch_Move = ((float)Pitch_Data) * 180 / 32768;
		Yaw_Move = ((float)Yaw_Data) * 180 / 32768;
	}
	else {};
}
