#ifndef __OLED_H
#define __OLED_H
#include "sys.h"

#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)(x))

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
 				    
#endif
