#ifndef __USART3_H
#define __USART3_H
#include "sys.h" 

#define EN_USART3_RX 1

extern float Roll_3,Pitch_3,Yaw_3;

void uart3_init(u32 bound);
void Read_Usart3(u8 TYPE_Data);
#endif


