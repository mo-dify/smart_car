#include "stm32f10x.h"
#include "timer2.h"
#include "timer.h"
#include "led.h"
#include	"usart1.h"
#include "usart2.h"
#include "usart3.h"



int main()
{
	//初始化led
	led_init();
	//舒适化串口1、
	usart_init1();
	//初始化定时器2
	timer2_init();
	//初始化定时时期3
	timer3_init(1000);
	//初始化串口2、3
	usart_init2();
	Uart3_Init(115200);
	//配置中断
	NVIC_Configuration1();
	delay1();
	reset_bit();
	//给dp_ch端口高电平，激活模块
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	delay1();
	//初始化wifi模块、并打开server服务
	wifi_init();
	while(1)
	{	
		//前进
		if(flag_w)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			TIM2->CCR1=30000;
			TIM2->CCR2=30000;
		}
		//后退
		if(flag_s)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			GPIO_SetBits(GPIOB,GPIO_Pin_12);
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
			GPIO_ResetBits(GPIOB,GPIO_Pin_13);
			TIM2->CCR1=30000;
			TIM2->CCR2=30000;
		}
		//顺时针旋转
		if(flag_a)
		{
			
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			GPIO_ResetBits(GPIOB,GPIO_Pin_13);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			TIM2->CCR1=30000;
			TIM2->CCR2=30000;
		}
		//逆时针旋转
		if(flag_d)
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			TIM2->CCR1=30000;
			TIM2->CCR1=30000;
			TIM2->CCR2=30000;
		}
	
	}
}
