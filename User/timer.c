#include "stm32f10x.h"
#include "timer.h"
#include "misc.h"
#include "usart2.h"
#include "usart1.h"

uint32_t Timer3_Count = 0;//记录Timer3中断次数
uint16_t Timer3_Frequency;//Timer3中断频率

int flag_1HZ=0;
uint32_t Timer3_Count100Hz = 0;
int flag_100HZ=0;
int delay_count = 0;


//初始化tim3定时器
void timer3_init(uint16_t Handler_Frequency)
{
	//定义一个定时器结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//打开桥时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	Timer3_Frequency=Handler_Frequency;
		TIM_DeInit(TIM3);
	//设置定时器结构体初始值
	TIM_TimeBaseStructure.TIM_Period=1000*1000/Handler_Frequency;
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	//调用定时器初始化函数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	//打开定时器
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//设定定时器中断
	TIM_Cmd(TIM3,ENABLE);
	//打开定时器中断

	//初始化中断结构体参数
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	//初始化中断
	NVIC_Init(&NVIC_InitStructure);

}


//定时器中断函数
void TIM3_IRQHandler(void)//Timer3中断
{
	if(TIM3->SR & TIM_IT_Update)//检查tim3定时器更新中断是否发生
	{     
		TIM3->SR = ~TIM_FLAG_Update;//清除中断标志
		//delay_count++;
		Timer3_Count++;
		delay_count++;
		if(Timer3_Count == 20)
		{
			USART_SendData(USART2,0x55);
			Timer3_Count=0;
		}
		if(Timer3_Count100Hz++ == 30)
			{
				if(lcs<100)
				{
					flag_w=0;
					flag_s=0;
					flag_a=0;
					flag_d=1;
				}
				else 
				{
					flag_w=1;
					flag_s=0;
					flag_a=0;
					flag_d=0
					;
				}
			Timer3_Count100Hz = 0;
		}
	}
}
//延迟
void ndelay(int ms)
{
	delay_count=0;
	while(delay_count<ms);
}
