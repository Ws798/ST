#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED�˿ڶ���
#define LED PBout(2)
#define LED_ON PBout(2)=1
#define LED_OFF PBout(2)=0

void LED_Init(void);//��ʼ��		 				    
#endif
