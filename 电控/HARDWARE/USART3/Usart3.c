#include "usart3.h"	

#if EN_USART3_RX   //如果使能了接收

u8 USART3_RxPacket[100];
u8 TYPE = 0;
u8 RxState = 0;
u8 pRxPacket = 0;
u8 RxData;
float Roll_3,Pitch_3,Yaw_3;

//初始化IO 串口1 
//bound:波特率
void uart3_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART3, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART3, ENABLE);  //使能串口1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART3_RX	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif
	
}



void USART3_IRQHandler(void)                	//串口1中断服务程序
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
////			len=USART3_RX_STA&0x3fff;//得到此次接收到的数据长度
////			for(t=0;t<len;t++)
////			{
////				num[t] = USART3_RX_BUF[t]; //存储数据				
////				USART_SendData(USART3, USART3_RX_BUF[t]);         //向串口3发送数据
////				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
////			}
////			USART3_RX_STA=0;
////			
////		}
////		return num[1];
//}
#endif	


