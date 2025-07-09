#ifndef __SERVO_H
#define __SERVO_H

#include "sys.h"

extern int E5_angle; //pitch
extern int E6_angle; //roll
extern int B8_angle; //on and under
extern int C9_angle; //left and right

void Servo_Init(void);
void Servo2_Init(void);
void Servo3_Init(void);
void Set_Servo_E5(int pwm);
void Set_Servo_E6(int pwm);
void Set_Servo_C9(int pwm);
void Set_Servo_B8(int pwm);

#endif

