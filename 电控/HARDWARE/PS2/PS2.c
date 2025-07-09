  /*****************************************************************************
  * @说  明
  *
  *   PS2数据定义
  *   BYTE   DATA   解释
  *   01     idle
  *   02     0x73   手柄工作模式
  *   03     0x5A   Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7
  *   04     data   SLCT  JOYR  JOYL  STRT   UP   RGIHT  DOWN   L
  *   05     data   L2     R2     L1    R1   /\     O     X    口
  *   06     data   右边摇杆  0x00 = 左    0xff = 右
  *   07     data   右边摇杆  0x00 = 上    0xff = 下
  *   08     data   左边摇杆  0x00 = 左    0xff = 右
  *   09     data   左边摇杆  0x00 = 上    0xff = 下
  * 
  ******************************************************************************
  */
	
#include "PS2.h"

//PS2手柄的输入输出口
#define DI()     PAin(4)      //数据输入引脚

#define CMD_H()   PAout(5)=1   //命令位高
#define CMD_L()   PAout(5)=0   //命令位低

#define CS_H()   PAout(6)=1    //CS拉高(别名ATT)
#define CS_L()   PAout(6)=0    //CS拉低(别名ATT)

#define CLK_H()  PAout(7)=1    //时钟拉高
#define CLK_L()  PAout(7)=0    //时钟拉低


const  uint8_t PS2_cmnd[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   //请求获取数据命令                         
static uint8_t PS2_data[9] = {0};  //接收的数据


/**
  * @简  述  PS2初始化
  * @参  数  无
  * @返回值  无
  */
void PS2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
	
	//DATA 信号从手柄到主机   输入口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//COMMMAND 信号从主机到手柄  输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//CS 手柄出发信号 信号在通信期间处于低电平	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//CLK 信号从主机到手柄   输出口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}


/**
  * @简  述  PS2数据读写函数
  * @参  数  data:要写入的数据
  * @返回值  读出数据
  */
static uint8_t PS2_ReadWriteData(uint8_t data)
{
	uint8_t ref,res;
	
	
	for(ref = 0x01; ref > 0x00; ref <<= 1)
	{
		CLK_L();
		if(ref&data)
			CMD_H();
		else
			CMD_L();	
		
		delay_us(16);
		
		CLK_H();
		if(DI())
			res |= ref; 
		
		delay_us(16);		
	}
	
	CMD_H();

	//返回读出数据
    return res;	
}

/**
  * @简  述  PS2获取按键及摇杆数值。
  * @参  数  *JoystickStruct 手柄键值结构体
  * @返回值  无
  */
void PS2_ScanKey(JOYSTICK_TypeDef *JoystickStruct)
{
	uint8_t i;
	
	//使能手柄
	CS_L();
	
	//读取PS2数据
	for(i=0; i<9; i++)
	{
		PS2_data[i] = PS2_ReadWriteData(PS2_cmnd[i]);
		delay_us(16);
	}
	
	//关闭使能
	CS_H();

	//数值传递
	JoystickStruct->mode = PS2_data[1];
	JoystickStruct->btn1 = ~PS2_data[3];
	JoystickStruct->btn2 = ~PS2_data[4];
	JoystickStruct->RJoy_LR = PS2_data[5];
	JoystickStruct->RJoy_UD = PS2_data[6];
	JoystickStruct->LJoy_LR = PS2_data[7];
	JoystickStruct->LJoy_UD = PS2_data[8];
}
