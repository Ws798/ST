#ifndef __MOTOR42_H
#define __MOTOR42_H

#include "sys.h"

extern u8 balance1_task;
extern u8 balance2_task;
extern float need_roll2;
extern float need_pitch2;
extern float need_roll3;
extern float need_pitch3;
extern u8 en_57,dir_57;
extern int dist_57;
extern int ndist_57;

void Motor42_Init(void);
void Control_42_x1(u8 en, u8 dir);
void Control_42_y1(u8 en, u8 dir);
void Control_42_x2(u8 en, u8 dir);
void Control_42_y2(u8 en, u8 dir);
void Control_57(u8 en, u8 dir);
u8 Balance1(void);
u8 Balance2(void);
void Dist_57(void);

#endif

