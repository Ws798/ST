#ifndef __TASK_H
#define __TASK_H

#include "sys.h"

#define Move_Ahead Speedl=Speedr=Speedm          //前进
#define Move_Back  Speedl=Speedr=-Speedm         //后退
#define Move_Left  Speedl=-Speedm;Speedr=Speedm  //左转
#define Move_Right Speedl=Speedm;Speedr=-Speedm  //右转
#define Move_Stop  Speedl=0;Speedr=0;            //停止

void Task_PS2(void);
void Task_Load(void);
void Task_ToBoard2(void);
void Task_Timer(void);
void Task_OLED(void);

#endif 
