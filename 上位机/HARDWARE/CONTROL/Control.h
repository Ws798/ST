#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"

void uart3_init(u32 bound);
void Control_SendByte(u8 Byte);
void Control_Sendstring(u8 *ucstr);

#endif
