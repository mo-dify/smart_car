#ifndef _USART2_H_
#define _USART2_H_

extern int lcs;
void usart_init2(void);
void putchar2(unsigned char c);
void delay2(void);
void USART2_IRQHandler(void);
#endif
