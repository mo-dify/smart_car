#include "stm32f10x_conf.h"
#include "misc.h"
#include "usart3.h"

int flag_w=0;
int flag_s=0;
int flag_a=0;
int flag_d=0;

//配置中端
void NVIC_Configuration1()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//在设置端口的时候，记得一定要设置这个游戏那几
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
//初始化串口
void usart_init1()
{
	GPIO_InitTypeDef GPIO_init;//初始化结构体
	USART_InitTypeDef USART_init;
	GPIO_StructInit(&GPIO_init);//利用库函数对结构体进行初始化
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

	GPIO_init.GPIO_Pin = GPIO_Pin_4;
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_init);
	
	
	//串口1所用外设接口初始化
	GPIO_init.GPIO_Pin = GPIO_Pin_9;//TX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_init);	
	GPIO_init.GPIO_Pin = GPIO_Pin_10;//RX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_init);
	//串口3初始化所用外设接口
	GPIO_init.GPIO_Pin = GPIO_Pin_10;//TX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_init);
	GPIO_init.GPIO_Pin = GPIO_Pin_11;//RX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_init);
	
	//串口3初始化
	USART_StructInit(&USART_init);//利用库函数进行初始化
	USART_init.USART_BaudRate=115200;
	USART_Init(USART1,&USART_init);
	
	USART_init.USART_WordLength=USART_WordLength_8b;
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//设置中断
	USART_Cmd(USART1,ENABLE);//启动串口

}

void uart1_putchar(unsigned char c)
{                               
    USART_SendData(USART1, c);                                   
    //while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
}
//延时
void delay1()
{
	int i,j;
	for(i=0;i<10000;i++)
		for(j=0;j<1000;j++);
}
//串口1中断函数
void USART1_IRQHandler(void)
{
  uint16_t l_tmp; //Received char from USART1
  
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);//清串口接收中断
    //Read one byte from the receive data register
    l_tmp  = USART_ReceiveData(USART1);
	//	USART3_PrintHexU8(l_tmp);
  }
  USART_ClearITPendingBit(USART1, USART_IT_ORE);//清串口总中断
}
//端口比特位清零
void reset_bit()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}
//判断客户端发出的命令、改变状态量
void check(uint8_t tmp)
{
		if(tmp=='w')
		{
			 flag_w=1;
			 flag_s=0;
			 flag_a=0;  
			flag_d=0;
		}
		if(tmp=='s')
		{
			flag_w=0;
			flag_s=1;
			flag_a=0;
			flag_d=0;
		}
		if(tmp=='a')
		{
			 flag_w=0;
			 flag_s=0;
			 flag_a=1;
			 flag_d=0;
		}
		if(tmp=='d')
		{
			 flag_w=0;
			 flag_s=0;
			 flag_a=0;
			 flag_d=1;
		}
		if(tmp=='p')
		{
			 flag_w=0;
			 flag_s=0;
			 flag_a=0;
			 flag_d=0;
			reset_bit();
		}
}
//处理客户端发送的数据
void b_check(uint8_t c)
{
	static int pos=1;
		if(pos==0 && c== 'I')
		{
			pos++;
		}
		if(pos==1 && c== 'P')
		{
			pos++;
		}	
		if(pos==2 && c== 'D')
		{
			pos++;
		}	
		if(pos==3 && c== ',')
		{
			pos++;
		}	
		if(pos==4 && c!=',')
		{
			pos++;
		}
		if(pos==5 && c==',')
		{
			pos++;
		}
		if(pos==6 && c!=',')
		{
			pos++;
		}
		if(pos==7 && c==':')
		{
			pos++;
		}
		else	
		   if(pos==8)
		{
			check(c);
			pos=1;
		}
}









