#include "Task.h"

u8 mode = PS2;
u8 blue;              //蓝牙命令
u8 flag_move = 0;     //移动标志
int set_speed1=0, set_speed2=0;
int go_set_speed=10000;
int speed1, speed2;   //编码器速度
u8 Toapp[7];					//angle[0]=roll,angle[1]=pitch
u8 flag_balance = 0;
u8 page;
u8 page_flag;
u8 page_do;
u8 count_load;

u8 flag_control=0;

u8 flag_jump[6];
u8 state_57=0;
u8 state_get=0;
int state_getdo=0;

float Roll_Value=23.7f;   //roll平稳值
float Pitch_Value=-3.0f;  //pitch平稳值

u16 c9=440;
u8 count_100ms;
u8 count_100msc;
u8 use_servo=0;
int ang[6];
int dis[6];
int dist=0;

void Timer_Task(void)
{
	static u8 led_state = 1;
	
	if(count_1ms >= 300) {page_flag = 1;count_1ms=0;}
	if(count_1ms % 100 == 0)
	{
		count_100ms = 1;
		led_state = ~led_state;
		count_load++;
//		printf("Roll1:%.2f, Pitch1:%.2f, Yaw1:%.2f \r\n", Roll_1, Pitch_1, Yaw_1);
//		printf("Roll2:%.2f, Pitch2:%.2f, Yaw2:%.2f \r\n", Roll_2, Pitch_2, Yaw_2);

		Toapp[1] = (int)Roll_3;
		Toapp[2] = (int)Pitch_3;
		Toapp[3] = (int)Roll_1;
		Toapp[4] = (int)Pitch_1;
		Toapp[5] = (int)Roll_2;
		Toapp[6] = (int)Pitch_2;
		Serial_SendArray(Toapp, 7);
	}
	LED = led_state;
	OLED_ShowNum(0, 0, count_load, 3, 12, 1);
}

void OLED_Task(void)  //OLED显示
{
	
	
	if((int)Roll_2>=0) OLED_ShowNum(0, 12, (int)Roll_2, 3, 12, 1);
	else if((int)Roll_2<=0) OLED_ShowNum(0, 12, -(int)Roll_2, 3, 12, 1);
	if((int)Pitch_2>=0) OLED_ShowNum(0, 24, (int)Pitch_2, 3, 12, 1);
	else if((int)Pitch_2<=0) OLED_ShowNum(0, 24, -(int)Pitch_2, 3, 12, 1);
	if((int)Yaw_2>=0) OLED_ShowNum(0, 36, (int)Yaw_2, 3, 12, 1);
	else if((int)Yaw_2<=0) OLED_ShowNum(0, 36, -(int)Yaw_2, 3, 12, 1);

	if((int)Roll_1>=0) OLED_ShowNum(24, 12, (int)Roll_1, 3, 12, 1);
	else if((int)Roll_1<=0) OLED_ShowNum(24, 12, -(int)Roll_1, 3, 12, 1);
	if((int)Pitch_1>=0) OLED_ShowNum(24, 24, (int)Pitch_1, 3, 12, 1);
	else if((int)Pitch_1<=0) OLED_ShowNum(24, 24, -(int)Pitch_1, 3, 12, 1);
	if((int)Yaw_1>=0) OLED_ShowNum(24, 36, (int)Yaw_1, 3, 12, 1);
	else if((int)Yaw_1<=0) OLED_ShowNum(24, 36, -(int)Yaw_1, 3, 12, 1);
	
	if((int)Roll_3>=0) OLED_ShowNum(48, 12, (int)Roll_3, 3, 12, 1);
	else if((int)Roll_3<=0) OLED_ShowNum(48, 12, -(int)Roll_3, 3, 12, 1);
	if((int)Pitch_3>=0) OLED_ShowNum(48, 24, (int)Pitch_3, 3, 12, 1);
	else if((int)Pitch_3<=0) OLED_ShowNum(48, 24, -(int)Pitch_3, 3, 12, 1);
	if((int)Yaw_3>=0) OLED_ShowNum(48, 36, (int)Yaw_3, 3, 12, 1);
	else if((int)Yaw_3<=0) OLED_ShowNum(48, 36, -(int)Yaw_3, 3, 12, 1);

	OLED_ShowChar(0, 50, blue_data, 12, 1);
	
	if(mode) {OLED_ShowString(84, 12, (u8 *)"PS2 ", 12, 1);}
	else if(!mode) {OLED_ShowString(84, 12, (u8 *)"BLUE", 12, 1);}
	
	
	OLED_ShowNum(114,52,go_set_speed/1000,2,12,1);
	OLED_ShowNum(114,24,set_speed1/1000,2,12,1);
	OLED_ShowNum(114,36,set_speed2/1000,2,12,1);
	
//	if(speed1 >= 0) {OLED_ShowNum(74,24,speed1,5,12,1);OLED_ShowChar(66,24,'+',12,1);}
//	else {OLED_ShowNum(74,24,-speed1,5,12,1);OLED_ShowChar(66,24,'-',12,1);}
//	if(speed2 >= 0) {OLED_ShowNum(74,36,speed2,5,12,1);OLED_ShowChar(66,36,'+',12,1);}
//	else {OLED_ShowNum(74,36,-speed2,5,12,1);OLED_ShowChar(66,36,'-',12,1);}
	OLED_Refresh();
	
//	
//	OLED_ShowNum(0, 12, volt/100, 2, 12, 1);
//	OLED_ShowNum(18, 12, volt%100, 2, 12, 1);
//	OLED_DrawPoint(15, 20, 1);
}

void Motor_Task(void) //电机任务
{
	if(go_set_speed >= 15000) {go_set_speed = 15000;}
	else if(go_set_speed <= 3000) {go_set_speed = 3000;}
	if(flag_move == 1)
	{
		Set_Speed(1, set_speed1);
		Set_Speed(2, set_speed2);
		speed1 = Read_Encoder(5);
		speed2 = Read_Encoder(4);
	}
}

void Key_Task(void)
{
	static u8 key = 0;
	if(count_key >= 5)
	{
		count_key = 0;
		key = KEY_Scan(0);
	}
	switch(key)
	{
		case 0: break;
		case 1: mode = BLUE; break;
		case 2: mode = PS2; break;	
	}
}

void Adc_Task(void)
{
//	volt = Get_ADC_Value();
}

void Servo_Task(void)
{
	static u8 flag_p=0, flag_p1, flag_p2;
	static u8 flag_r=1, flag_r1, flag_r2;
	
	if(c9 >= 2600) c9=2600;
	else if(c9 <= 400) c9=400;
	
	if(B8_angle >= 2600) B8_angle=2600;
	else if(B8_angle <= 400) B8_angle=400;
	if(C9_angle >= 2600) C9_angle=2600;
	else if(C9_angle <= 400) C9_angle=400;
	if(E5_angle >= 2500) E5_angle=2500;
	else if(E5_angle <= 500) E5_angle=500;
	if(E6_angle >= 2500) E6_angle=2500;
	else if(E6_angle <= 500) E6_angle=500;
	
	Set_Servo_E5(E5_angle);
	Set_Servo_E6(E6_angle);
	//E5++,Pitch_1--; E6++,Roll--;
	if(flag_balance == 1)
	{
		if(flag_p==0)
		{
			if(Pitch_1 >= Pitch_Value) flag_p1=1;
			else flag_p2=1;
			if(flag_p1 && !flag_p2)
			{
				if(Pitch_1 - Pitch_Value >= 12) E5_angle+=50;
				else if(Pitch_1 - Pitch_Value >= 9) E5_angle+=25;
				else if(Pitch_1 - Pitch_Value >= 6) E5_angle+=15;
				else if(Pitch_1 - Pitch_Value >= 3) E5_angle+=10;
				else if(Pitch_1 - Pitch_Value >= 1) E5_angle+=5;
				else E5_angle+=1;
			}
			else if(!flag_p1 && flag_p2) 
			{
				if(Pitch_1 - Pitch_Value <= -12) E5_angle-=50;
				else if(Pitch_1 - Pitch_Value <= -9) E5_angle-=25;
				else if(Pitch_1 - Pitch_Value <= -6) E5_angle-=15;
				else if(Pitch_1 - Pitch_Value <= -3) E5_angle-=10;
				else if(Pitch_1 - Pitch_Value <= -1) E5_angle-=5;
				else E5_angle-=1;
			}
			else if(flag_p1 && flag_p2) {flag_p1=flag_p2=0; flag_p=1, flag_r=0;}
		}
		if(flag_r==0)
		{
			if(Roll_1 >= Roll_Value) flag_r1=1;
			else flag_r2=1;
			if(flag_r1 && !flag_r2)
			{
				if(Roll_1 - Roll_Value >= 12) E6_angle+=50;
				else if(Roll_1 - Roll_Value >= 9) E6_angle+=25;
				else if(Roll_1 - Roll_Value >= 6) E6_angle+=15;
				else if(Roll_1 - Roll_Value >= 3) E6_angle+=10;
				else if(Roll_1 - Roll_Value >= 1) E6_angle+=5;
				else E6_angle+=1;
			}
			else if(!flag_r1 && flag_r2)
			{
				if(Roll_1 - Roll_Value <= -12) E6_angle-=50;
				else if(Roll_1 - Roll_Value <= -9) E6_angle-=25;
				else if(Roll_1 - Roll_Value <= -6) E6_angle-=15;
				else if(Roll_1 - Roll_Value <= -3) E6_angle-=10;
				else if(Roll_1 - Roll_Value <= -1) E6_angle-=5;
				else E6_angle-=1;
			}
			else if(flag_r1 && flag_r2) {flag_r1=flag_r2=0; flag_p=0, flag_r=1; flag_balance=0;}
		}
	}
}

void Usart1_Task(void)  //串口1
{
	u8 t;
	u8 len;	
	u8 num;

	if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
//			printf("\r\n您发送的消息为:\r\n");
			for(t=0;t<len;t++)
			{
				num = USART_RX_BUF[t]; //存储数据
				OLED_ShowChar(36, 0, num, 12, 1);
				if(num == '3')
				{
					OLED_ShowNum(24, 0, 6, 1, 12, 1);
					page = page_angle;
				}
				else if(num == '2')
				{
					OLED_ShowNum(24, 0, 0, 1, 12, 1);
					page = page_main;
				}
				
				USART_SendData(USART1, USART_RX_BUF[t]);         //向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
//			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}
}

void PS2_Task(void)  //PS2任务
{
	static JOYSTICK_TypeDef my_joystick; 
	PS2_ScanKey(&my_joystick);
	if(my_joystick.mode == 0x73)
	{
		//运动
		if(my_joystick.LJoy_UD == 0x7f && my_joystick.LJoy_LR == 0x80) blue = Stop;
		switch(my_joystick.LJoy_UD)
		{
			case 0x00: blue = Ahead; break;
			case 0xff: blue = Back; break;
			default: break;
		}
		switch(my_joystick.LJoy_LR)
		{
			case 0x00: blue = Left; break;
			case 0xff: blue = Right; break;
			default: break;
		}
		switch(my_joystick.btn1)
		{
			case 0x02: mode = BLUE; break;
			case 0x04: need_roll2=Roll_2;need_pitch2=Pitch_2;need_roll3=Roll_3;need_pitch3=Pitch_3; break;
			default: break;
		}
		//摆臂
		switch(my_joystick.btn2)
		{
			case 0x08: Swing_Control(1, 1); break;
			case 0x02: Swing_Control(1, -1); break;
			case 0x04: Swing_Control(2, 1); break;
			case 0x01: Swing_Control(2, -1); break;
			case 0x00: Swing_Control(1, 0);Swing_Control(2, 0);break;
			default: break;
		}
		//舵机
		switch(my_joystick.RJoy_UD)
		{
			case 0x00: B8_angle-=20; Set_Servo_B8(B8_angle); break;
			case 0xff: B8_angle+=20; Set_Servo_B8(B8_angle); break;
			default: break;
		}
		switch(my_joystick.RJoy_LR)
		{
			case 0x00: C9_angle+=20;Set_Servo_C9(C9_angle);use_servo=1; break;
			case 0xff: C9_angle-=20;Set_Servo_C9(C9_angle);use_servo=1; break;
			default: break;
		}
		//57步进电机and加减速
		switch(my_joystick.btn1)
		{
			case 0x80: en_57=1;dir_57=0; break;
			case 0x20: en_57=1;dir_57=1; break;
			case 0x10: go_set_speed+=1000; break;
			case 0x40: go_set_speed-=1000; break;
			case 0x00: en_57=0;dir_57=0; break;
			default: break;
		}
		
		switch(my_joystick.btn2)
		{
			case 0x10: flag_balance=1;balance1_task=1;balance2_task=1; break;
			case 0x20: state_getdo++;state_57=1; break;
			case 0x40: state_get++;dist_57=0; break;
			case 0x80: state_getdo--;state_57=1; break;
			default: break;
		}
	}
	

//	printf("MODE:%2x BTN1:%2x BTN2:%2x RJOY_LR:%2x RJOY_UD:%2x LJOY_LR:%2x LJOY_UD:%2x\r\n",
//	my_joystick.mode, my_joystick.btn1, my_joystick.btn2, 
//	my_joystick.RJoy_LR, my_joystick.RJoy_UD, my_joystick.LJoy_LR, my_joystick.LJoy_UD);
}

void Do_State(void)
{
	if(state_getdo <= 0) state_getdo=0;
	else if(state_getdo >= 30) state_getdo=30;
	if(state_getdo<5) {ndist_57=0;flag_jump[1]=flag_jump[2]=flag_jump[3]=flag_jump[4]=1;if((ndist_57==dist_57)&&!use_servo) C9_angle=ang[0];}
	else if(state_getdo<10) {ndist_57=dis[1];C9_angle=440;flag_jump[2]=flag_jump[3]=flag_jump[4]=1;if((ndist_57==dist_57)&&!use_servo) {C9_angle=ang[1];Data_dump1();}}
	else if(state_getdo<15) {ndist_57=dis[2];flag_jump[1]=flag_jump[3]=flag_jump[4]=1;if((ndist_57==dist_57)&&!use_servo) {C9_angle=ang[2];Data_dump2();}}
	else if(state_getdo<20) {ndist_57=dis[3];flag_jump[1]=flag_jump[2]=flag_jump[4]=1;if((ndist_57==dist_57)&&!use_servo) {C9_angle=ang[3];Data_dump3();}}
	else if(state_getdo<25) {ndist_57=dis[4];flag_jump[1]=flag_jump[2]=flag_jump[3]=1;if((ndist_57==dist_57)&&!use_servo) {C9_angle=ang[4];Data_dump4();}}
	else if(state_getdo<30) {ndist_57=dis[5];flag_jump[2]=flag_jump[3]=flag_jump[4]=1;if((ndist_57==dist_57)&&!use_servo) C9_angle=ang[5];Data_dump1();}
	if(!use_servo)
	{
		Set_Servo_C9(C9_angle);
	}
	
}

void Blue_Task(void)
{
	if(blue_flag == 1)
	{
		blue_flag = 0;
		switch(blue_data)
		{
			case 'a': blue = Ahead;use_servo=0; break;
			case 'b': blue = Back;break;
			case 'c': blue = Left;break;
			case 'd': blue = Right;break;
			case 'e': blue = Speed_up;break;
			case 'f': blue = Speed_down;break;
			case 'g': blue = Stop;break;
			case 'h': blue = Swing1_up;break;
			case 'i': blue = Swing1_down;break;
			case 'j': blue = Swing1_stop;break;
			case 'k': blue = Swing2_up;break;
			case 'l': blue = Swing2_down;break;
			case 'm': blue = Swing2_stop;break;
			case 'n': blue = Case_left;break;
			case 'o': blue = Case_right;break;
			case 'p': blue = Reset_57;break;
			case 'q': blue = Balance_1;break;
			case 'r': blue = Balance_2;break;
			case 's': blue = Balance_3;break;
			case 't': blue = Balance_all;break;
			case 'u': blue = Cloud_up;break;
			case 'v': blue = Cloud_down;break;
			case 'w': blue = Cloud_left;break;
			case 'x': blue = Cloud_right;break;
			case 'y': blue = Mode_switch;break;
			case 'z': blue = Jiaozhun;break;
		}
	}
}

void Do_Task(void)
{
	switch(blue)
	{
		case Stop:  set_speed1=0; set_speed2=0; blue=0; break;
		case Ahead: flag_move=1; set_speed1=set_speed2=go_set_speed; blue=0; break;
		case Left:  set_speed1=-go_set_speed; set_speed2=go_set_speed; blue=0; break;
		case Right: set_speed1=go_set_speed; set_speed2=-go_set_speed; blue=0; break;
		case Back:  set_speed1=set_speed2=-go_set_speed; blue=0; break;
		case Speed_up: go_set_speed+=1000; blue=0; break;
		case Speed_down: go_set_speed-=1000; blue=0; break;
		case Swing1_up: Swing_Control(2, 1); blue=0; break;
		case Swing1_down: Swing_Control(2, -1);blue=0; break;
		case Swing1_stop: Swing_Control(2, 0);blue=0; break;
		case Swing2_up: Swing_Control(1, -1);blue=0; break;
		case Swing2_down: Swing_Control(1, 1);blue=0; break;
		case Swing2_stop: Swing_Control(1, 0);blue=0; break;
		case Case_left: state_getdo-=5;state_57=1;Do_State();blue=0; break;
		case Case_right: state_getdo+=5;state_57=1;Do_State();blue=0; break;
		case Reset_57: dist_57=0;blue=0; break;
		case Balance_1: blue=0;balance2_task=1; break;
		case Balance_2: blue=0;balance1_task=1; break;
		case Balance_3: blue=0;flag_balance=1; break;
		case Balance_all: blue=0;flag_balance=1;balance1_task=1;balance2_task=1; break;
		case Cloud_up: blue=0;B8_angle-=20;Set_Servo_B8(B8_angle); break;
		case Cloud_down: blue=0;B8_angle+=20;Set_Servo_B8(B8_angle); break;
		case Cloud_left: blue=0;C9_angle+=20; Set_Servo_C9(C9_angle);use_servo=1; break;
		case Cloud_right: blue=0;C9_angle-=20; Set_Servo_C9(C9_angle);use_servo=1; break;
		case Mode_switch: blue=0;mode=PS2; break;
		case Jiaozhun: blue=0;need_roll2=Roll_2;need_pitch2=Pitch_2;need_roll3=Roll_3;need_pitch3=Pitch_3; break;
	}
}

void LCD_Task(void)
{
	static u8 do_flag;
	if(page_flag)
	{
		page_flag = 0;
		switch(page)
		{
			case page_main : do_flag=page_main;
											 printf("speed.txt=\"%d\"\xff\xff\xff", go_set_speed/150);
										 	 if(mode) {printf("mode.txt=\"PS2\"\xff\xff\xff");}
											 else if(!mode) {printf("mode.txt=\"APP\"\xff\xff\xff");}
											 break;
			case page_angle: printf("t9.txt=\"%.5f\"\xff\xff\xff", Roll_1);
											 printf("t0.txt=\"%.5f\"\xff\xff\xff", Roll_2);
											 printf("t6.txt=\"%.5f\"\xff\xff\xff", Roll_3);
											 printf("t10.txt=\"%.5f\"\xff\xff\xff", Pitch_1);	
											 printf("t3.txt=\"%.5f\"\xff\xff\xff", Pitch_2);	
											 printf("t7.txt=\"%.5f\"\xff\xff\xff", Pitch_3);
											 do_flag=page_angle; break;
			case page_celiang: printf("servo.txt=\"%d\"\xff\xff\xff", C9_angle);
											   printf("dist.txt=\"%d\"\xff\xff\xff", dist_57);
										   	 printf("time.txt=\"%d\"\xff\xff\xff", state_getdo);
												 printf("num.txt=\"%d\"\xff\xff\xff", dist);
											 switch(dist)
											 {
												 case 1: printf("dis0.txt=\"%d\"\xff\xff\xff", dis[1]);printf("ag0.txt=\"%d\"\xff\xff\xff", ang[1]/10);break;
												 case 2: printf("dis1.txt=\"%d\"\xff\xff\xff", dis[2]);printf("ag1.txt=\"%d\"\xff\xff\xff", ang[2]/10);break;
												 case 3: printf("dis2.txt=\"%d\"\xff\xff\xff", dis[3]);printf("ag2.txt=\"%d\"\xff\xff\xff", ang[3]/10);break;
												 case 4: printf("dis3.txt=\"%d\"\xff\xff\xff", dis[4]);printf("ag3.txt=\"%d\"\xff\xff\xff", ang[4]/10);break;
												 case 5: printf("dis4.txt=\"%d\"\xff\xff\xff", dis[5]);printf("ag4.txt=\"%d\"\xff\xff\xff", ang[5]/10);break;
												 default:break;
											 }
											   do_flag=page_celiang; break;
			case page_control: do_flag=page_control; break;
			default: break;
		}
	}
	switch(do_flag)
	{
		case page_angle: if(page_do == page_do_balance) {page_do=page_do_no;balance1_task=1;balance2_task=1;flag_balance=1;}
										 else if(page_do == page_do_jiaozheng) {page_do=page_do_no;need_roll2=Roll_2;need_pitch2=Pitch_2;need_roll3=Roll_3;need_pitch3=Pitch_3;}
										 break;
		case page_main:  if(page_do == page_do_xmode)
										 {
											 page_do=page_do_no;
											 if(mode==PS2) mode=BLUE;
											 else if(mode==BLUE) mode=PS2;
										 }
										 break;
		case page_celiang: if(page_do == page_do_down) {page_do=page_do_no;if(dist++>=5) dist=1;}
											 else if(page_do == page_do_on) {page_do=page_do_no;if(dist--<=1) dist=5;}
											 else if(page_do == page_do_ok) {page_do=page_do_no;dis[dist]=dist_57;ang[dist]=C9_angle;}
											 else if(page_do == page_do_res) {page_do=page_do_no;dist=0;}
											 break;
		case page_control: if(page_do == page_do_ControlA) {flag_control=page_do_ControlA;}
											 else if(page_do == page_do_ControlB) {flag_control=page_do_ControlB;}
											 else if(page_do == page_do_ControlC) {flag_control=page_do_ControlC;}
											 else if(page_do == page_do_ControlD) {flag_control=page_do_ControlD;}
											 else if(page_do == page_do_ControlE) {E6_angle+=10;}
											 else if(page_do == page_do_ControlF) {E6_angle-=10;}
											 else if(page_do == page_do_ControlG) {E5_angle-=10;}
											 else if(page_do == page_do_ControlH) {E5_angle+=10;}
											 else if(page_do == page_do_ControlI) {flag_control=page_do_ControlI;}
											 else if(page_do == page_do_ControlJ) {flag_control=page_do_ControlJ;}
											 else if(page_do == page_do_ControlK) {flag_control=page_do_ControlK;}
											 else if(page_do == page_do_ControlL) {flag_control=page_do_ControlL;}
											 else if(page_do == page_do_ControlM) {page_do=page_do_no;flag_control=page_do_ControlM;}
											 break;
		default: break;
	}
}

void Data_dump1(void)
{
	static u8 state=14;
	static u8 start=1;
	if(flag_jump[1]==1)
	{
		flag_jump[1] = 0;
		state = 14;
		start = 1;
	}
	if(state <= 0)
	{
		start = 0;
	}
	if(start && (count_100ms==1))
	{
		state--;
		count_100ms = 0;
		if(state%2 == 1)
		{
			Toapp[0]=113+state;
		}
		else if(state%2 == 0)
		{
			Toapp[0]=114-state;
		}
	}
}
void Data_dump2(void)
{
	static u8 state=10;
	static u8 start=1;
	if(flag_jump[2]==1)
	{
		flag_jump[2] = 0;
		state = 10;
		start = 1;
	}
	if(state <= 0)
	{
		start = 0;
	}
	if(start && (count_100ms==1))
	{
		state--;
		count_100ms = 0;
		if(state%2 == 1)
		{
			Toapp[0]=109+state;
		}
		else if(state%2 == 0)
		{
			Toapp[0]=110-state;
		}
	}
}
void Data_dump3(void)
{
	static u8 state=10;
	static u8 start=1;
	if(flag_jump[3]==1)
	{
		flag_jump[3] = 0;
		state = 10;
		start = 1;
	}
	if(state <= 0)
	{
		start = 0;
	}
	if(start && (count_100ms==1))
	{
		state--;
		count_100ms = 0;
		if(state%2 == 1)
		{
			Toapp[0]=117+state;
		}
		else if(state%2 == 0)
		{
			Toapp[0]=118-state;
		}
	}
}
void Data_dump4(void)
{
	static u8 state=8;
	static u8 start=1;
	if(flag_jump[4]==1)
	{
		flag_jump[4] = 0;
		state = 8;
		start = 1;
	}
	if(state <= 0)
	{
		start = 0;
	}
	if(start && (count_100ms==1))
	{
		state--;
		count_100ms = 0;
		if(state%2 == 1)
		{
			Toapp[0]=107+state;
		}
		else if(state%2 == 0)
		{
			Toapp[0]=108-state;
		}
	}
}


