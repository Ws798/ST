#include "Task.h"

void Task_Reboard1(void)
{
	if(Res_board1_flag)  //开发板1传来数据
	{
		switch(Res_board1)
		{
//			case '1': LED_ON; break;
//			case '2': LED_OFF; break;
//			case '3': LED_ON; break;
//			case '4': LED_OFF; break;
//			case '5': LED_ON; break;
			default : break;
		}
	}
	
}

void Task_OLED(void)
{
	OLED_ShowHexNum(1, 1, Res_board1, 2); //开发板1数据显示
	OLED_ShowNum(1, 11, movetime/20000, 3);
	OLED_ShowSignedNum(2, 1, Roll_Move, 3);
	OLED_ShowSignedNum(2, 6, Pitch_Move, 3);
	OLED_ShowSignedNum(2, 11, Yaw_Move, 3);
	OLED_ShowSignedNum(3, 1, Roll_Notmove, 3);
	OLED_ShowSignedNum(3, 6, Pitch_Notmove, 3);
	OLED_ShowSignedNum(3, 11, Yaw_Notmove, 3);
	OLED_ShowSignedNum(4, 1, Roll_Camera, 3);
	OLED_ShowSignedNum(4, 6, Pitch_Camera, 3);
	OLED_ShowSignedNum(4, 11, Yaw_Camera, 3);
}

