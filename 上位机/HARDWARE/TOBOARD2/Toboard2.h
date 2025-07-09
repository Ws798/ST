#ifndef __TOBOARD2_H
#define __TOBOARD2_H

#include "sys.h"

void uart2_init(u32 bound);
void To_SendByte(u8 Byte);
void To_Sendstring(u8 *ucstr);

#endif
