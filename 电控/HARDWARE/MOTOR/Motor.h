#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"

#define M1_H1 GPIO_SetBits(GPIOC,GPIO_Pin_4)   //电机1一边置1
#define M1_L1 GPIO_ResetBits(GPIOC,GPIO_Pin_4) //电机1一边置0
#define M1_H2 GPIO_SetBits(GPIOC,GPIO_Pin_5)   //电机1二边置1
#define M1_L2 GPIO_ResetBits(GPIOC,GPIO_Pin_5) //电机1二边置0

#define M2_H1 GPIO_ResetBits(GPIOB,GPIO_Pin_1)  //电机2一边置0
#define M2_L1 GPIO_SetBits(GPIOB,GPIO_Pin_1)	  //电机2一边置1
#define M2_H2 GPIO_ResetBits(GPIOB,GPIO_Pin_0)  //电机2二边置0
#define M2_L2 GPIO_SetBits(GPIOB,GPIO_Pin_0)    //电机2二边置1

#define M3_H1 GPIO_SetBits(GPIOE,GPIO_Pin_8)   //电机3一边置1
#define M3_L1 GPIO_ResetBits(GPIOE,GPIO_Pin_8) //电机3一边置0
#define M3_H2 GPIO_SetBits(GPIOE,GPIO_Pin_10)  //电机3二边置1
#define M3_L2 GPIO_ResetBits(GPIOE,GPIO_Pin_10)//电机3二边置0

#define M4_H1 GPIO_SetBits(GPIOE,GPIO_Pin_12)  //电机4一边置1
#define M4_L1 GPIO_ResetBits(GPIOE,GPIO_Pin_12)//电机4一边置0
#define M4_H2 GPIO_SetBits(GPIOE,GPIO_Pin_15)  //电机4二边置1
#define M4_L2 GPIO_ResetBits(GPIOE,GPIO_Pin_15)//电机4二边置0

void Move_PWM_Init(uint16_t arr,uint16_t psc);
void Move_Init(void);
void Swing_Init(void);

void Set_Speed(int num, int speed);
void Swing_Control(int num, int dir);

#endif
