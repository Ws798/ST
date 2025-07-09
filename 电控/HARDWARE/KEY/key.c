#include "key.h"

//������ʼ������
void KEY_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOA,GPIOEʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //KEY0 ��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOE4
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//WK_UP��Ӧ����PA0
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOA0
 
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY1����
//2��KEY2����
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	
	if(mode) key_up=1;  //֧������
	if(key_up&&(KEY1==0||KEY2==0))
	{
		key_up=0;
		if(KEY1==0) return KEY1_PRES;
		else if(KEY2==0) return KEY2_PRES; 
	}		
	else
	{
		key_up = 1;
	}
 	return 0;// �ް�������
}




















