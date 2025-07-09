  /*****************************************************************************
  * @˵  ��
  *
  *   PS2���ݶ���
  *   BYTE   DATA   ����
  *   01     idle
  *   02     0x73   �ֱ�����ģʽ
  *   03     0x5A   Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7
  *   04     data   SLCT  JOYR  JOYL  STRT   UP   RGIHT  DOWN   L
  *   05     data   L2     R2     L1    R1   /\     O     X    ��
  *   06     data   �ұ�ҡ��  0x00 = ��    0xff = ��
  *   07     data   �ұ�ҡ��  0x00 = ��    0xff = ��
  *   08     data   ���ҡ��  0x00 = ��    0xff = ��
  *   09     data   ���ҡ��  0x00 = ��    0xff = ��
  * 
  ******************************************************************************
  */
	
#include "PS2.h"

//PS2�ֱ������������
#define DI()     PAin(4)      //������������

#define CMD_H()   PAout(5)=1   //����λ��
#define CMD_L()   PAout(5)=0   //����λ��

#define CS_H()   PAout(6)=1    //CS����(����ATT)
#define CS_L()   PAout(6)=0    //CS����(����ATT)

#define CLK_H()  PAout(7)=1    //ʱ������
#define CLK_L()  PAout(7)=0    //ʱ������


const  uint8_t PS2_cmnd[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   //�����ȡ��������                         
static uint8_t PS2_data[9] = {0};  //���յ�����


/**
  * @��  ��  PS2��ʼ��
  * @��  ��  ��
  * @����ֵ  ��
  */
void PS2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
	
	//DATA �źŴ��ֱ�������   �����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//COMMMAND �źŴ��������ֱ�  ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//CS �ֱ������ź� �ź���ͨ���ڼ䴦�ڵ͵�ƽ	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//CLK �źŴ��������ֱ�   �����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}


/**
  * @��  ��  PS2���ݶ�д����
  * @��  ��  data:Ҫд�������
  * @����ֵ  ��������
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

	//���ض�������
    return res;	
}

/**
  * @��  ��  PS2��ȡ������ҡ����ֵ��
  * @��  ��  *JoystickStruct �ֱ���ֵ�ṹ��
  * @����ֵ  ��
  */
void PS2_ScanKey(JOYSTICK_TypeDef *JoystickStruct)
{
	uint8_t i;
	
	//ʹ���ֱ�
	CS_L();
	
	//��ȡPS2����
	for(i=0; i<9; i++)
	{
		PS2_data[i] = PS2_ReadWriteData(PS2_cmnd[i]);
		delay_us(16);
	}
	
	//�ر�ʹ��
	CS_H();

	//��ֵ����
	JoystickStruct->mode = PS2_data[1];
	JoystickStruct->btn1 = ~PS2_data[3];
	JoystickStruct->btn2 = ~PS2_data[4];
	JoystickStruct->RJoy_LR = PS2_data[5];
	JoystickStruct->RJoy_UD = PS2_data[6];
	JoystickStruct->LJoy_LR = PS2_data[7];
	JoystickStruct->LJoy_UD = PS2_data[8];
}
