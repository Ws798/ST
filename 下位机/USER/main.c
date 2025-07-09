#include "sys.h"

int main(void)
{ 
	Sys_Init();
	while(1)
	{
		Task_Reboard1();
		Task_OLED();
	}
}

