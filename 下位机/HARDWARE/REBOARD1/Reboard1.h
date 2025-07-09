#ifndef __REBOARD1_H
#define __REBOARD1_H

#include "sys.h"

extern u8 Res_board1;
extern u8 Res_board1_flag;

void uart2_init(u32 bound);
void Re_SendByte(u8 Byte);
void Re_Sendstring(u8 *ucstr);

#endif
