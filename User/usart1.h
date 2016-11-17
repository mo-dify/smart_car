#ifndef _USART1_H_
#define _USART1_H_
#include "stm32f10x.h"
extern int flag_w;
extern int flag_s;
extern int flag_a;
extern int flag_d;
extern int flag;

void usart_init1(void);
void uart1_putchar(unsigned char c);
void delay1(void);
void check(uint8_t tmp);
void b_check(uint8_t c);
void reset_bit(void);
#endif
