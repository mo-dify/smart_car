#ifndef _TIMER_H_
#define _TIMER_H_
#include "stm32f10x_conf.h"

extern int flag_1HZ;
extern int flag_100HZ;

void timer3_init(uint16_t Handler_Frequency);
void ndelay(int ms);
#endif
