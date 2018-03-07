/**********************************************************
* @ File name -> usart.c
* @ Version   -> V1.0
* @ Date      -> 12-26-2013
* @ Brief     -> 系统串口设置相关的函数
**********************************************************/

#include "usart.h"

/**********************************************************
   加入以下代码，支持printf函数，而不需要选择use MicroLIB
**********************************************************/

#if 1

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR & 0x40) == 0);	//循环发送，直到发送完毕   
    USART1->DR = (uint8_t)ch;	//发送数据      
	return ch;
}
#endif

/**********************   end   **************************/


/**********************************************************
* 函数功能 ---> 初始化IO 串口1
* 入口参数 ---> bound：波特率	
* 返回数值 ---> none
* 功能说明 ---> none
**********************************************************/
void USART1_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
#ifdef EN_USART1_RX	//如果使能了接收中断
	
	USART1->CR1 |= 1 << 8;	//PE中断使能
	USART1->CR1 |= 1 << 5;	//接收缓冲区非空中断使能
	
	MY_NVIC_Init(3, 3, USART1_IRQn, NVIC_PriorityGroup_2);	//中断分组2，最低优先级
	
#endif
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
		
	USART_DeInit(USART1);  //复位串口1
	
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10
  
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;	//设置波特率，一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;	//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	USART_Init(USART1, &USART_InitStructure); //初始化串口
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART1, ENABLE);                    //使能串口 
}

//=========================================================
 
#ifdef EN_USART1_RX   //如果使能了接收

//=========================================================

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误 

uint8_t USART_RX_BUF[USART_REC_LEN];	//接收缓冲,最大USART_REC_LEN个字节

//接收状态
//bit15：接收完成标志
//bit14：接收到0x0d
//bit13~0：接收到的有效字节数目，最大512字节

uint16_t USART_RX_STA=0;	//接收状态标记	  

/**********************************************************
* 函数功能 ---> 串口1接收中断服务程序
* 入口参数 ---> none	
* 返回数值 ---> none
* 功能说明 ---> none
**********************************************************/
void USART1_IRQHandler(void)
{
	uint8_t res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收到数据
	{
		res = USART_ReceiveData(USART1);	//读取接收到的数据
		
		if((USART_RX_STA & 0x8000) == 0)//接收未完成
		{
			if(USART_RX_STA & 0x4000)//接收到了0x0d
			{
				/***********************************************
                                  修改内容如下
                    当用户数据当中有0x0d的时候修正的错误的判断
				***********************************************/
				
				if(res != 0x0a)
				{
					USART_RX_BUF[USART_RX_STA & 0x3fff] = 0x0d;	//补上丢失的0x0d数据
					USART_RX_STA++;
					USART_RX_BUF[USART_RX_STA & 0x3fff] = res;	//继续接收数据
					USART_RX_STA++;
					USART_RX_STA &= 0xbfff;						//清除0x0d标志
				}
				
				/***********************************************
                                      修改完成
				***********************************************/
				
				else	USART_RX_STA |= 0x8000;	//接收完成了
			}
			else //还没收到0x0d
			{	
				if(res == 0x0d)	USART_RX_STA |= 0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA & 0x3fff] = res;
					USART_RX_STA++;
					if(USART_RX_STA > (USART_REC_LEN - 1))	USART_RX_STA = 0;//接收数据错误,重新开始接收	  
				}		 
			}
		}	//end 接收未完成   		 
	}	//end 接收到数据
}

//=========================================================

#endif	//end使能接收

//=========================================================

