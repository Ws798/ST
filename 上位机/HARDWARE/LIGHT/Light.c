#include "Light.h"

//#define uart5_dataZERO memset(uart5_data, 0, 7)
#define uart5_dataZERO uart5_data[0]=uart5_data[1]=uart5_data[2]=uart5_data[3]=uart5_data[4]=uart5_data[5]=uart5_data[6]=uart5_p=0
#define Light485R_GET Light_value=uart5_data[3]<<8|uart5_data[4]

u8 uart5_p;
u32 Light_value; //读出的光照亮度
unsigned char uart5_data[7] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char Light485T[8] = {0x01,0x03,0x00,0x07,0x00,0x01,0x35,0xCB};
//串口5
void uart5_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
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
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
    
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Init(UART5,&USART_InitStructure);   
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	USART_Cmd(UART5,ENABLE);
}

void UART5_IRQHandler(void)                	//串口5中断服务程序
{
	if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{
		uart5_data[uart5_p++] = USART_ReceiveData(UART5);
		/*前三位后两位校验，以防数据丢失造成的误判*/
		if(uart5_data[0]!=0x01) uart5_dataZERO;
		else if(uart5_p==2 && uart5_data[1]!=0x03) uart5_dataZERO;
		else if(uart5_p==3 && uart5_data[2]!=0x02) uart5_dataZERO;
		else if(uart5_p==7 && (uart5_data[5]==0x00||uart5_data[5]==0x01||uart5_data[5]==0x02||uart5_data[5]==0x03||uart5_data[6]==0x00||uart5_data[6]==0x01||uart5_data[6]==0x02||uart5_data[6]==0x03)) uart5_dataZERO;
		/*前三位后两位校验，以防数据丢失造成的误判*/
		if(uart5_p >= 7) {Light485R_GET;uart5_dataZERO;} //数据写入
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
	}
}

void Light_SendByte(u8 Byte)
{
	USART_SendData(UART5, (u8)Byte);
	while (USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
}

void Light_SendArray(u8 *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Light_SendByte(Array[i]);
	}
}

void Get_Light(void)
{
	Light_SendArray(Light485T, 8);
}

