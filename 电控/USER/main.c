#include "sys.h"

extern u8 mode;

int main(void)
{
	System_Init();
	
	while(1)
	{			
		Timer_Task();
		Usart1_Task();
		Motor_Task();
		Key_Task();
		if(mode) {PS2_Task();}
		else if(!mode) {Blue_Task();}
		Do_State();
		Do_Task();
//		Adc_Task();
		OLED_Task();
		Servo_Task();
		LCD_Task();
	}
}
