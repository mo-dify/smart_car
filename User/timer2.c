#include "timer2.h"


//初始化tim2定时器
void timer2_init()
{
	//打开tim2的时钟
	RCC->APB1ENR |= 0x01;
	//打开gpioA的时钟
	//RCC->APB2ENR |=	0x5;
	RCC->APB2ENR |= 1<<2;
	
	//reset低8位
	GPIOA->CRL &=0xffffff00;
	//1010复用推挽输出，输出速度2hz
	GPIOA->CRL |=0xaa;
	//分频，方便计数
	TIM2->PSC=71;
	//设置周期
	TIM2->ARR=50000;
	TIM2->CCMR1=0x7070;
	TIM2->CCMR1|=1<<3;
	TIM2->CCMR1|=1<<11;
	TIM2->CR1|=1<<7;
	TIM2->CCER|=0x11;
	TIM2->CR1 |=0x1;

}
