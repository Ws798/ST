#ifndef __TASK_H
#define __TASK_H

#include "sys.h"

#define Stop 200
#define Ahead 201
#define Left 202
#define Right 203
#define Back 204
#define Speed_up 205
#define Speed_down 206
#define Swing1_up 207
#define Swing1_down 208
#define Swing1_stop 209
#define Swing2_up 210
#define Swing2_down 211
#define Swing2_stop 212
#define Case_left 213
#define Case_right 214
#define Reset_57 215
#define Balance_1 216
#define Balance_2 217
#define Balance_3 218
#define Balance_all 219
#define Cloud_left 220
#define Cloud_right 221
#define Cloud_up 222
#define Cloud_down 223
#define Mode_switch 224
#define Jiaozhun 225


#define PS2 1
#define BLUE 0

#define page_main 2
#define page_angle 3
#define page_control 5
#define page_celiang 7
#define page_do_no 100
#define page_do_balance 101
#define page_do_jiaozheng 102
#define page_do_xmode 103
#define page_do_on 104
#define page_do_down 105
#define page_do_res 106
#define page_do_ok 107
#define page_do_ControlA 108
#define page_do_ControlB 109
#define page_do_ControlC 110
#define page_do_ControlD 111
#define page_do_ControlE 112
#define page_do_ControlF 113
#define page_do_ControlG 114
#define page_do_ControlH 115
#define page_do_ControlI 116
#define page_do_ControlJ 117
#define page_do_ControlK 118
#define page_do_ControlL 119
#define page_do_ControlM 120


void OLED_Task(void);
void Motor_Task(void);
void Adc_Task(void);
void Usart1_Task(void);
void PS2_Task(void);
void Blue_Task(void);
void Key_Task(void);
void Do_Task(void);
void Servo_Task(void);
void LCD_Task(void);
void Timer_Task(void);
void Do_State(void);
void Data_dump1(void);
void Data_dump2(void);
void Data_dump3(void);
void Data_dump4(void);

extern u8 page;
extern u8 page_do;
extern u8 state_57;
extern u8 state_get;
extern int state_getdo;
extern int ang[6];
extern int dis[6];
extern u8 flag_control;
extern u8 Toapp[7];
#endif
