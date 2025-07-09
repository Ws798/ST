#include "sys.h"

int main(void)
{ 
	Sys_Init();
	while(1)
	{
		parseGpsBuffer();
		printGpsBuffer();
		Task_PS2();
		Task_Load();
		Task_ToBoard2();
		Task_Timer();
		Task_OLED();
	}
}
