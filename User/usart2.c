#include "stm32f10x_conf.h"
#include "misc.h"
#include "usart1.h"

int lcs=101;
static int lh;
static int ll;

//配置串口2中断
void NVIC_Configuration2()
{
	NVIC_InitTypeDef NCVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NCVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NCVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NCVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NCVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NCVIC_InitStructure);
}
//初始化串口
void usart_init2()
{
	GPIO_InitTypeDef GPIO_init;//初始化结构体
	USART_InitTypeDef USART_init;
	GPIO_StructInit(&GPIO_init);//利用库函数对结构体进行初始化
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	//修改结构体的部分数据
	GPIO_init.GPIO_Pin = GPIO_Pin_2;//TX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP;
	//利用库函数对ping教进行初始化
	GPIO_Init(GPIOA,&GPIO_init);
	
	GPIO_init.GPIO_Pin = GPIO_Pin_3;//RX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_init);
	USART_StructInit(&USART_init);//利用库函数进行初始化
	USART_init.USART_BaudRate=9600;
	USART_Init(USART2,&USART_init);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//设置中断
	USART_Cmd(USART2,ENABLE);//启动串口
	NVIC_Configuration2();//调用出初始化
}
//通过串口2发送数据
void putchar2(unsigned char c)
{
	USART_SendData(USART2,c);
}
//延时
void delay2()
{
	int i,j;
	for(i=0;i<10000;i++)
		for(j=0;j<1000;j++);
}

//串口2中断函数、判断超声波模块反馈的数据
void USART2_IRQHandler()
{
	static int flag=0;
	int tmp;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);
			tmp=USART_ReceiveData(USART2);
			if(flag==0)
			{
				lh=tmp;
				flag=1;
			}
			else
			{
					ll=tmp;
					lcs=ll*256+lh;
					flag=0;
			}
	}	
	USART_ClearITPendingBit(USART2,USART_IT_ORE);
}


