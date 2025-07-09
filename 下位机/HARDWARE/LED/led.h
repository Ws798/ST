#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED端口定义
#define LED PBout(2)
#define LED_ON PBout(2)=1
#define LED_OFF PBout(2)=0

void LED_Init(void);//初始化		 				    
#endif
