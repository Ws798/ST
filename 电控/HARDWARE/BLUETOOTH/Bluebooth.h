#ifndef __BLUEBOOTH_H
#define __BLUEBOOTH_H

#include "sys.h"

extern u8 blue_data;
extern u8 blue_flag;

void uart2_init(u32 bound);
void Serial_SendByte(u8 Byte);
void Serial_SendArray(u8 *Array, uint16_t Length);

#endif

