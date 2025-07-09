#include "Task.h"

u8 tx=0x00;
u8 Command; //����

JOYSTICK_TypeDef my_joystick;//PS2�ṹ��
int Speedl = 0,  //�����ٶ�
	  Speedr = 0;  //�����ٶ�
u8	Speedm = 50; //��ֵ�ٶ�
u8  Ahead_Mode = Turn_Stop, //ǰ�ڱ�ģʽ
		Back_Mode  = Turn_Stop; //������ģʽ

void Task_PS2(void)
{
	PS2_ScanKey(&my_joystick); //��ȡPS2��ֵ
	
	if(my_joystick.mode == 0x73)//PS2ģʽ
	{
		/*�ƶ�*/
		if(my_joystick.LJoy_UD == 0x7f && my_joystick.LJoy_LR == 0x80) Move_Stop;
		switch(my_joystick.LJoy_UD)
		{
			case 0x00: Move_Ahead; break;
			case 0xff: Move_Back; break;
			default: break;
		}
		switch(my_joystick.LJoy_LR)
		{
			case 0x00: Move_Left; break;
			case 0xff: Move_Right; break;
			default: break;
		}
		/*ǰ�ڱۣ�������*/
		switch(my_joystick.btn2)
		{
			case 0x08: Back_Mode=Turn_Ahead; break;
			case 0x02: Back_Mode=Turn_back; break;
			case 0x04: Ahead_Mode=Turn_Ahead; break;
			case 0x01: Ahead_Mode=Turn_back; break;
			case 0x00: Ahead_Mode=Back_Mode=Turn_Stop; break;
			default: break;
		}
		/*�����*/
		switch(my_joystick.btn1)
		{
//			case 0x80: en_57=1;dir_57=0; break;
//			case 0x20: en_57=1;dir_57=1; break;
			case 0x10: BIGLED_ON; break;
			case 0x40: BIGLED_OFF; break;
//			case 0x00: en_57=0;dir_57=0; break;
			default: break;
		}
	}

}

void Task_Load(void)
{
	Ahead(Ahead_Mode);
	Back(Back_Mode);
	Move(Speedl, Speedr);
}

void Task_ToBoard2(void)
{
//	u8 i, j;
//	for(i=0; i<=9; i++)
//	{
//		j = i + '0';
//		To_SendByte(j);
//		delay_ms(1000);
//	}
	
}

void Task_Timer(void)
{
	if(count_timer>=5)  //0.5s
	{
		count_timer = 0;
		Get_Light();
		if(Light_value<=30) {BIGLED_ON;}
		else {BIGLED_OFF;}
//		Get_GPS = !Get_GPS;
//		LED_TRIG;
	}
}

void Task_OLED(void)
{
	OLED_ShowNum(1, 1, Light_value, 4);
	OLED_ShowNum(1, 8, count_timer, 1);
	if(GPS_flag == 1)
	{
		/************��ʾN************/
		OLED_ShowNum(3, 1, f_latitude, 3);
		OLED_ShowChar(3, 4, '.');OLED_ShowChar(3, 11, 'N');
		OLED_ShowNum(3, 5, (u32)(f_latitude*1000000)%1000000, 6);
		/************��ʾN************/
		/************��ʾE************/
		OLED_ShowNum(4, 1, f_longitude, 3);
		OLED_ShowChar(4, 4, '.');OLED_ShowChar(4, 11, 'E');
		OLED_ShowNum(4, 5, (u32)(f_longitude*1000000)%1000000, 6);
		/************��ʾE************/
	}
	else
	{
		OLED_ShowString(3, 1, "Not GPS_SIG");
		OLED_ShowString(4, 1, "Not GPS_SIG");
	}
	
}
