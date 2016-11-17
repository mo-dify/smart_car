#ifndef _USART3_H_
#define _USART3_H_
#include "stm32f10x_conf.h"

void Uart3_Init(uint32_t baud);
void USART3_PrintHexU8(uint8_t data);
void delay3(void);
void USART3_IRQHandler(void);
void wifi_init(void);
uint8_t USART_GdtHexU8(void);
#endif
