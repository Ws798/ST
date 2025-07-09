#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"

#define Ahead_Speed 80 //前摆臂速度
#define Back_Speed  80 //后三角速度
#define Turn_Stop   0 	//摆臂，三角停止
#define Turn_Ahead  1  //摆臂，三角向前
#define Turn_back   2  //摆臂，三角向后

void Motor_Init(void);
void Set(void);
void Move(int s1, int s2);
void Ahead(u8 mode);
void Back(u8 mode);

#endif
