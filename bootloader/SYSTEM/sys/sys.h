/**********************************************************
* @ File name -> sys.h
* @ Version   -> V1.0.1
* @ Date      -> 03-09-2014
* @ Brief     -> 系统设置相关的函数头文件

 V1.0.1
* @ Revise    -> 增加GPIO共用初始化函数，方便在移植时直接宏定义即可
**********************************************************/

#ifndef _sys_h_
#define _sys_h_

/**********************************************************
                     外部函数头文件                        
**********************************************************/
	
#include "stm32f10x.h"

#include "string.h"
#include "stdio.h"
//#include "alloc.h"

/**********************************************************
定义是否支持嵌入式操作系统
**********************************************************/

#define _SYSTEM_SUPPORT_ROTS					0	/* 嵌入式操作系统支持开关 */
													//0：不支持
													//1：支持

/**********************************************************
                      动态数据表管理
**********************************************************

#define MaxSize					100	//设置最大的连续空间

typedef uint16_t	ElemType;	//定义数据类型

typedef struct
{
	ElemType *elem;		//顺序表的首地址
	uint16_t length;	//顺序表的长度（表中元素的个数）
	uint16_t listsize;	//顺序表占用内存空间的大小（以sizeof(ElemType)为单位，由MaxSize规定）
}Sqlist;
																	 */
/**********************************************************
                    JTAG模式设置定义
**********************************************************/

#define JTAG_SWD_Enable			0x00000000	//复位值
#define JNTRST_Disable			0x00000001	//JNTRST引脚释放
#define SWD_Enable				0x00000010	//JTAG关闭，SWD开启
#define JTAG_SWD_Disable		0x00000100	//JTAG和SWD都关闭

/**********************************************************
                    位带操作相关宏定义
              参考《CM3权威指南》第87 ~ 92页
**********************************************************/

#define BITBAND(addr, bitnum)			((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)					*((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)			MEM_ADDR(BITBAND(addr, bitnum)) 

/**********************************************************
                       GPIO地址映射
              基地址加上寄存器偏移地址组成
**********************************************************/

#define GPIOA_ODR_Addr    (GPIOA_BASE+12)	//0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12)	//0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12)	//0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12)	//0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12)	//0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12)	//0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12)	//0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8)	//0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8)	//0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8)	//0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8)	//0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8)	//0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8)	//0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8)	//0x40011E08 

/**********************************************************
             实现单一IO操作，类似于51的IO操作
                   n值要小于IO具体数目
**********************************************************/ 

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

/**********************************************************
                     外部调用功能函数
**********************************************************/

void STM32_Flash_Capacity(uint8_t *STMCapa);	//读取芯片闪存容量

void STM32_CPUID(uint8_t *IDbuff);	//读取CPUID

void STM_Clock_Init(uint8_t pll);	//系统时钟初始化

void MY_NVIC_SetVectorTable(uint32_t NVIC_VectTab,uint32_t Offset);	//设置向量表偏移地址

void MY_NVIC_PriorityGroup_Config(uint32_t NVIC_PriorityGroup);	//设置中断分组

void MY_NVIC_Init(uint8_t NVIC_PreemptionPriority,uint8_t NVIC_Subpriority,uint8_t NVIC_Channel,uint32_t NVIC_Group);


void MY_RCC_DeInit(void);	//所有时钟寄存器复位

void SYS_Standby(void);	//设置芯片进入待机模式

void SYS_SoftReset(void);	//系统软复位

void STM_JTAG_Set(uint32_t mode);	//JTAG模式设置


uint8_t BCD_to_HEX(uint8_t BCD_Data);	//BCD码转为HEX

uint8_t HEX_to_BCD(uint8_t HEX_Data);	//HEX码转为BCD

uint16_t DX_to_HX(uint16_t DX_Data);	//10进制码转为16进制

uint16_t HX_to_DX(uint16_t HX_Data);	//16进制码转为10进制


void STM32_GPIOx_Init(
                        uint32_t RCC_APB2Periph,		/* GPIO对应时钟 */
						GPIO_TypeDef* GPIOx,			/* 所对应的GPIO组 */
						uint16_t GPIO_Pinx,				/* GPIO对应的管脚号 */
						GPIOSpeed_TypeDef GPIO_SPEED,	/* GPIO翻转速度 */
						GPIOMode_TypeDef GPIO_MODE		/* GPIO设置模式 */
					   );


//void Sqlist_Init(Sqlist *LIST);	//初始化数据列表
//void Sqlist_DeInit(void);	//复位数据列表
//void InsertElem(Sqlist *L,uint16_t i,ElemType item);	//向一个动态的数据列表插入一个元素


#endif

