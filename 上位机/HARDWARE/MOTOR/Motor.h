#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"

#define Ahead_Speed 80 //ǰ�ڱ��ٶ�
#define Back_Speed  80 //�������ٶ�
#define Turn_Stop   0 	//�ڱۣ�����ֹͣ
#define Turn_Ahead  1  //�ڱۣ�������ǰ
#define Turn_back   2  //�ڱۣ��������

void Motor_Init(void);
void Set(void);
void Move(int s1, int s2);
void Ahead(u8 mode);
void Back(u8 mode);

#endif
