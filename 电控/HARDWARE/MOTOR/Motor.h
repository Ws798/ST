#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"

#define M1_H1 GPIO_SetBits(GPIOC,GPIO_Pin_4)   //���1һ����1
#define M1_L1 GPIO_ResetBits(GPIOC,GPIO_Pin_4) //���1һ����0
#define M1_H2 GPIO_SetBits(GPIOC,GPIO_Pin_5)   //���1������1
#define M1_L2 GPIO_ResetBits(GPIOC,GPIO_Pin_5) //���1������0

#define M2_H1 GPIO_ResetBits(GPIOB,GPIO_Pin_1)  //���2һ����0
#define M2_L1 GPIO_SetBits(GPIOB,GPIO_Pin_1)	  //���2һ����1
#define M2_H2 GPIO_ResetBits(GPIOB,GPIO_Pin_0)  //���2������0
#define M2_L2 GPIO_SetBits(GPIOB,GPIO_Pin_0)    //���2������1

#define M3_H1 GPIO_SetBits(GPIOE,GPIO_Pin_8)   //���3һ����1
#define M3_L1 GPIO_ResetBits(GPIOE,GPIO_Pin_8) //���3һ����0
#define M3_H2 GPIO_SetBits(GPIOE,GPIO_Pin_10)  //���3������1
#define M3_L2 GPIO_ResetBits(GPIOE,GPIO_Pin_10)//���3������0

#define M4_H1 GPIO_SetBits(GPIOE,GPIO_Pin_12)  //���4һ����1
#define M4_L1 GPIO_ResetBits(GPIOE,GPIO_Pin_12)//���4һ����0
#define M4_H2 GPIO_SetBits(GPIOE,GPIO_Pin_15)  //���4������1
#define M4_L2 GPIO_ResetBits(GPIOE,GPIO_Pin_15)//���4������0

void Move_PWM_Init(uint16_t arr,uint16_t psc);
void Move_Init(void);
void Swing_Init(void);

void Set_Speed(int num, int speed);
void Swing_Control(int num, int dir);

#endif
