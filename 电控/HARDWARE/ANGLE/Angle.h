#ifndef __ANGLE_H
#define __ANGLE_H
#include "sys.h" 
extern float Roll_1,Pitch_1,Yaw_1;
extern float Roll_2,Pitch_2,Yaw_2;
void uart4_init(u32 bound);
void Read_Uart4(u8 TYPE_Data);
void uart5_init(u32 bound);
void Read_Uart5(u8 TYPE_Data);
#endif


