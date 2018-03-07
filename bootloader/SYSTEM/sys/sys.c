/**********************************************************
* @ File name -> sys.c
* @ Version   -> V1.0.1
* @ Date      -> 03-09-2014
* @ Brief     -> 系统设置相关的函数

 V1.0.1
* @ Revise    -> 增加GPIO共用初始化函数，方便在移植时直接宏定义即可
**********************************************************/

#include "sys.h"

/**********************************************************
* 函数功能 ---> STM32 GPIO输出方向初始化
* 入口参数 ---> *STMCapa：容量字符显示缓存
* 返回数值 ---> none
* 功能说明 ---> 按照此函数形参的顺序进行宏定义即可
**********************************************************/
void STM32_GPIOx_Init(
                        uint32_t RCC_APB2Periph,		/* GPIO对应时钟 */
						GPIO_TypeDef* GPIOx,			/* 所对应的GPIO组 */
						uint16_t GPIO_Pinx,				/* GPIO对应的管脚号 */                       
						GPIOSpeed_TypeDef GPIO_SPEED,	/* GPIO翻转速度 */
						GPIOMode_TypeDef GPIO_MODE		/* GPIO设置模式 */
					   )
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//检测输入参数
	assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
	assert_param(IS_GPIO_PIN(GPIO_Pinx));
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_SPEED(GPIO_SPEED));
	assert_param(IS_GPIO_MODE(GPIO_MODE)); 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	//开启外设时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE;

	GPIO_Init(GPIOx, &GPIO_InitStructure);	//初始化GPIO相关结构体
}
/**********************************************************
* 函数功能 ---> 读取芯片闪存容量
* 入口参数 ---> *STMCapa：容量字符显示缓存
* 返回数值 ---> none
* 功能说明 ---> none
**********************************************************/
void STM32_Flash_Capacity(uint8_t *STMCapa)
{
	uint16_t capa;
	
	capa = *((uint16_t*)0x1ffff7e0);	//读取闪存容量寄存器，低16位有效
	
	capa = ((capa >> 12) * 4096 + ((capa >> 8) & 0x0f) * 256 + ((capa >> 4) & 0x0f) * 16 + (capa & 0x0f));	//转换成十进制
	
	STMCapa[0] = 0x4d;	//M
	STMCapa[1] = 0x43;	//C
	STMCapa[2] = 0x55;	//U
	STMCapa[3] = 0x43;	//C
	STMCapa[4] = 0x61;	//a
	STMCapa[5] = 0x70;	//p
	STMCapa[6] = 0x3a;	//:
	
	if((capa / 1000) != 0)	STMCapa[7] = capa / 1000 + 48;	//千位不为0时显示
	else	STMCapa[7] = 0x20;
	
	STMCapa[8] = capa % 1000 / 100 + 48;	//百位
	STMCapa[9] = capa % 100 /10 + 48;		//十位
	STMCapa[10] = capa % 10 + 48;			//个位
	STMCapa[11] = 0x4b;	//K
	STMCapa[12] = 0x62;	//b
}
/**********************************************************
* 函数功能 ---> 读取CPUID
* 入口参数 ---> 存储CPUID缓存（字符串输出）
* 返回数值 ---> none
* 功能说明 ---> none
**********************************************************/
void STM32_CPUID(uint8_t *IDbuff)
{
	uint32_t CPUID;
	CPUID = *((uint32_t*)0xe000ed00);
	sprintf((char*)IDbuff, "CPU ID:%08X", CPUID);
}
/**********************************************************
* 函数功能 ---> 设置向量表偏移地址
* 入口参数 ---> NVIC_VectTab：基址
*                             SRAM_BASE：内部SRAM地址(或：NVIC_VectTab_RAM)
*                             FLASH_BASE：内部FLASH地址(或：NVIC_VectTab_FLASH)
*               Offset：偏移量	
* 返回数值 ---> none
* 功能说明 ---> none
**********************************************************/	 
void MY_NVIC_SetVectorTable(uint32_t NVIC_VectTab,uint32_t Offset)	 
{
	//检测输入参数
	assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
	assert_param(IS_NVIC_OFFSET(Offset));
	 	   	 
	SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1fffff80);//设置NVIC的向量表偏移寄存器
	//用于标识向量表是在CODE区还是在RAM区
}
/**********************************************************
* 函数功能 ---> 设置中断分组
* 入口参数 ---> NVIC_PriorityGroup: 中断分组
* 返回数值 ---> none
* 功能说明 ---> 0 ~ 4组，共计有5组
**********************************************************/
void MY_NVIC_PriorityGroup_Config(uint32_t NVIC_PriorityGroup)
{
	//检测输入参数
	assert_param(IS_NVIC_PRIORITY_GROUP(NVIC_PriorityGroup));

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup);	//设置中断分组
	
//	uint32_t temp,temp1;
//	
//	temp1 = (~NVIC_PriorityGroup) & 0x00000007;//取后三位
//	temp1 <<= 8;
//	temp = SCB->AIRCR;  //读取先前的设置
//	temp &= 0x0000f8ff; //清空先前分组
//	temp |= 0x05fa0000; //写入钥匙
//	temp |= temp1;	   
//	SCB->AIRCR = temp;  //设置分组
}
/**********************************************************
* 函数功能 ---> 设置中断分组优先级
* 入口参数 ---> NVIC_PreemptionPriority：抢先优先级
*               NVIC_Subpriority：响应优先级
*               NVIC_Channel：中断编号
*               NVIC_Group: 中断分组
* 返回数值 ---> none
* 功能说明 ---> 1、组划分:
*                  组0：0位抢占优先级，4位响应优先级
*                  组1：1位抢占优先级，3位响应优先级
*                  组2：2位抢占优先级，2位响应优先级
*                  组3：3位抢占优先级，1位响应优先级
*                  组4：4位抢占优先级，0位响应优先级
*               2、抢先优先级参数和响应优先级参数原则上是数值越小优先级越高
**********************************************************/
void MY_NVIC_Init(uint8_t NVIC_PreemptionPriority,uint8_t NVIC_Subpriority,uint8_t NVIC_Channel,uint32_t NVIC_Group)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//检测输入参数
	assert_param(IS_NVIC_PREEMPTION_PRIORITY(NVIC_PreemptionPriority));  
	assert_param(IS_NVIC_SUB_PRIORITY(NVIC_Subpriority));
	
	MY_NVIC_PriorityGroup_Config(NVIC_Group);	//设置中断分组	
	
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_Channel;								//设置中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PreemptionPriority;	//抢先优先级  	 	 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_Subpriority;				//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;									//使能中断

	NVIC_Init(&NVIC_InitStructure);	//初始化中断
	
//	uint32_t temp;	
//	uint8_t IPRADDR=NVIC_Channel/4;  //每组只能存4个,得到组地址 
//	uint8_t IPROFFSET=NVIC_Channel%4;//在组内的偏移
//	
//	IPROFFSET = IPROFFSET*8 + 4;    //得到偏移的确切位置
//	
//	MY_NVIC_PriorityGroup_Config(NVIC_Group);//设置分组
//	
//	temp  = NVIC_PreemptionPriority << (4 - NVIC_Group);	//抢先优先级	  
//	temp |= NVIC_Subpriority & (0x0f >> NVIC_Group);	//相应优先级
//	temp &= 0xf;//取低四位

//	if(NVIC_Channel < 32)	NVIC->ISER[0] |= 1 << NVIC_Channel;//使能中断位(要清除的话,相反操作就OK)
//	else	NVIC->ISER[1]| |= 1 << (NVIC_Channel - 32); 
//	
//	NVIC->IPR[IPRADDR] |= temp << IPROFFSET;//设置响应优先级和抢断优先级  
}
/**********************************************************
* 函数功能 ---> THUMB指令不支持汇编内联
* 入口参数 ---> none
* 返回数值 ---> none
* 功能说明 ---> 采用如下方法实现执行汇编指令WFI
**********************************************************/
__asm void WFI_SET(void)
{
	WFI;    
}
/**********************************************************
* 函数功能 ---> 所有时钟寄存器复位
* 入口参数 ---> none
* 返回数值 ---> none
* 功能说明 ---> 不能在这里执行所有外设复位!否则至少引起串口不工作
**********************************************************/
void MY_RCC_DeInit(void)
{										  					   
	RCC->APB1RSTR = 0x00000000;	//复位结束			 
	RCC->APB2RSTR = 0x00000000; 
	  
  	RCC->AHBENR   = 0x00000014;	//睡眠模式闪存和SRAM时钟使能.其他关闭.	  
  	RCC->APB2ENR  = 0x00000000;	//外设时钟关闭.			   
  	RCC->APB1ENR  = 0x00000000;   
	RCC->CR      |= 0x00000001;	//使能内部高速时钟HSION	 															 
	RCC->CFGR    &= 0xf8ff0000;	//复位SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR      &= 0xfef6ffff;	//复位HSEON,CSSON,PLLON
	RCC->CR      &= 0xfffbffff;	//复位HSEBYP	   	  
	RCC->CFGR    &= 0xff80ffff;	//复位PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR      = 0x00000000;	//关闭所有中断
	
	//配置向量表				  
#ifdef  VECT_TAB_RAM
	MY_NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);	//内部SRAM起始地址
#else   
	MY_NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);	//内部FLASH起始地址
#endif
}
/**********************************************************
* 函数功能 ---> 设置芯片进入待机模式
* 入口参数 ---> none
* 返回数值 ---> none
* 功能说明 ---> 利用WKUP引脚唤醒（PA.0）
**********************************************************/
void SYS_Standby(void)
{
	SCB->SCR |= 1 << 2;			//使能sleep deep（SYS->CTRL）
	RCC->APB1ENR |= 1 << 28;	//电源接口时钟开启
	PWR->CSR |= 1 << 8;			//设置WKUP引脚用于唤醒
	PWR->CR |= 1 << 2;			//清除WAKE-UP标志
	PWR->CR |= 1 << 1;			//PDDS置位，掉电深睡眠
	WFI_SET();					//执行WFI指令
}
/**********************************************************
* 函数功能 ---> 系统软复位
* 入口参数 ---> none
* 返回数值 ---> none
* 功能说明 ---> none
**********************************************************/
void SYS_SoftReset(void)
{
	SCB->AIRCR = 0x05fa0000 | 0x00000004;
}
/**********************************************************
* 函数功能 ---> JTAG模式设置
* 入口参数 ---> mode：模式参数（详细宏定义见sys.h中定义）
*                    000：JTAG-DP + SW-DP（复位状态）
*                    001：JTAG-DP + SW-DP（除了JNTRST引脚，释放JRST引脚）
*                    010：JTAG-DP接口禁止，SW-DP接口允许
*                    100：JTAG-DP接口和SW-DP接口都禁止
*                    xxx：其他值，禁止
* 返回数值 ---> none
* 功能说明 ---> none
**********************************************************/
void STM_JTAG_Set(uint32_t mode)
{
	RCC->APB2ENR |= 1 << 0;		//使能辅助时钟
	AFIO->MAPR &= 0xf8ffffff;	//清除SWJ_CFG[2:0]位，即【26:24】
	AFIO->MAPR |= (mode << 24);	//设置JTAG模式
}
/**********************************************************
* 函数功能 ---> 系统时钟初始化
* 入口参数 ---> pll：倍频数。取值范围：2 ~ 16
* 返回数值 ---> none
* 功能说明 ---> none
**********************************************************/
void STM_Clock_Init(uint8_t pll)
{
	uint8_t tmp = 0;
	
	MY_RCC_DeInit();	//复位并配置向量表，并且将外部中断和外设时钟全部关闭
	
	RCC->CR |= 0x00010000;  //外部高速时钟使能HSEON
	
	while(!(RCC->CR >> 17));//等待外部时钟就绪
	
	RCC->CFGR = 0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	pll -= 2;//抵消2个单位
	RCC->CFGR |= pll << 18;   //设置PLL值 2~16
	RCC->CFGR |= 1 << 16;	  //PLLSRC ON 
	FLASH->ACR |= 0x32;	  //FLASH 2个延时周期

	RCC->CR |= 0x01000000;  //PLLON
	
	while(!(RCC->CR >> 25));//等待PLL锁定
	
	RCC->CFGR |= 0x00000002;//PLL作为系统时钟，最后才能开启PLL，因为设定PLL时，PLL相关位必须在关闭状态下进行
	
	while(tmp != 0x02)     //等待PLL作为系统时钟设置成功
	{   
		tmp  = RCC->CFGR >> 2;
		tmp &= 0x03;
	}    
}
/**********************************************************
* 函数功能 ---> BCD码转为HEX
* 入口参数 ---> BCD_Data：要转换的BCD数据
* 返回数值 ---> HEX码
* 功能说明 ---> none
**********************************************************/	
uint8_t BCD_to_HEX(uint8_t BCD_Data)
{
	return((BCD_Data / 10) << 4 | (BCD_Data % 10));
}
/**********************************************************
* 函数功能 ---> HEX码转为BCD
* 入口参数 ---> HEX_Data：要转换的BCD数据
* 返回数值 ---> BCD码
* 功能说明 ---> none
**********************************************************/	
uint8_t HEX_to_BCD(uint8_t HEX_Data)
{
	return((HEX_Data >> 4) * 10 + (HEX_Data & 0x0f));
}
/**********************************************************
* 函数功能 ---> 10进制码转为16进制
* 入口参数 ---> DX_Data：要转换的10进制数据
* 返回数值 ---> 16进制
* 功能说明 ---> none
**********************************************************/
uint16_t DX_to_HX(uint16_t DX_Data)
{
	return(((DX_Data/1000)<<12) | ((DX_Data%1000/100)<<8) | ((DX_Data%100/10)<<4) | (DX_Data%10));
}
/**********************************************************
* 函数功能 ---> 16进制码转为10进制
* 入口参数 ---> HX_Data：要转换的16进制数据
* 返回数值 ---> 10进制
* 功能说明 ---> none
**********************************************************/
uint16_t HX_to_DX(uint16_t HX_Data)
{
	return((HX_Data>>12)*1000+((HX_Data&0x0f00)>>8)*100+((HX_Data&0x00f0)>>4)*10+(HX_Data&0x000f));
}	

///**********************************************************
//* 函数功能 ---> 初始化数据列表
//* 入口参数 ---> *LIST：列表指针
//* 返回数值 ---> none
//* 功能说明 ---> none
//**********************************************************/
//void Sqlist_Init(Sqlist *LIST)
//{
//	LIST->elem = (uint16_t*)malloc(MaxSize * sizeof(ElemType));
//	//分配一个长度为MaxSize * sizeof(ElemType)大小的内存空间
//	if(!LIST->elem)	return;	//没有生成数据列表，直接退出
//	//分配成功
//	LIST->length = 0;	//列表中没内容
//	LIST->listsize = MaxSize;	//该数据表占用内存大小为MaxSize（以sizeof(ElemType)为单位）
//}
///**********************************************************
//* 函数功能 ---> 复位数据列表
//* 入口参数 ---> none
//* 返回数值 ---> none
//* 功能说明 ---> none
//**********************************************************/
//void Sqlist_DeInit(void)
//{
//	Sqlist *list;
//
//	list->elem = 0;	//首地址清零
//	list->length = 0;	//长度清零
//	list->listsize = 0;	//列表大小为0
//}
///**********************************************************
//* 函数功能 ---> 向一个动态的数据列表插入一个元素
//* 入口参数 ---> *L：列表指针
//*               i：列表中第i个位置插入元素
//*               item：在第i个位置所插入的元素
//* 返回数值 ---> none
//* 功能说明 ---> none
//**********************************************************/
//void InsertElem(Sqlist *L,uint16_t i,ElemType item)
//{	/* 向顺序列表*L的第i个位置插入元素item */
//	ElemType *base, *insertPtr, *p;
//
//	if(i < 1 || i > L->length + 1)	return;	//非法插入
//	if(L->length >= L->listsize)	//在数据列表最后一个位置插入元素
//	{	//追加内存空间
//		base = (ElemType*)realloc(L->elem,(L->listsize + 10) * sizeof(ElemType));
//		L->elem = base;	//更新内存基地址
//		L->listsize = L->listsize + 100;	//存储空间增加100个单元
//	}
//	insertPtr = &(L->Elem[i - 1]);	//insertPtr为插入位置
//	for(p = &(L->elem[L->length - 1]);p >= insertPtr;p--)
//		*(p + 1) = *p;	//将i - 1以后的元素顺序向后移一个元素位置
//	*insertPtr = item;	//在第i个位置上插入元素item
//	L->length++;	//表长加1
//}

