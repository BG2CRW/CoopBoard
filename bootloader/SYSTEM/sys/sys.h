/**********************************************************
* @ File name -> sys.h
* @ Version   -> V1.0.1
* @ Date      -> 03-09-2014
* @ Brief     -> ϵͳ������صĺ���ͷ�ļ�

 V1.0.1
* @ Revise    -> ����GPIO���ó�ʼ����������������ֲʱֱ�Ӻ궨�弴��
**********************************************************/

#ifndef _sys_h_
#define _sys_h_

/**********************************************************
                     �ⲿ����ͷ�ļ�                        
**********************************************************/
	
#include "stm32f10x.h"

#include "string.h"
#include "stdio.h"
//#include "alloc.h"

/**********************************************************
�����Ƿ�֧��Ƕ��ʽ����ϵͳ
**********************************************************/

#define _SYSTEM_SUPPORT_ROTS					0	/* Ƕ��ʽ����ϵͳ֧�ֿ��� */
													//0����֧��
													//1��֧��

/**********************************************************
                      ��̬���ݱ����
**********************************************************

#define MaxSize					100	//�������������ռ�

typedef uint16_t	ElemType;	//������������

typedef struct
{
	ElemType *elem;		//˳�����׵�ַ
	uint16_t length;	//˳���ĳ��ȣ�����Ԫ�صĸ�����
	uint16_t listsize;	//˳���ռ���ڴ�ռ�Ĵ�С����sizeof(ElemType)Ϊ��λ����MaxSize�涨��
}Sqlist;
																	 */
/**********************************************************
                    JTAGģʽ���ö���
**********************************************************/

#define JTAG_SWD_Enable			0x00000000	//��λֵ
#define JNTRST_Disable			0x00000001	//JNTRST�����ͷ�
#define SWD_Enable				0x00000010	//JTAG�رգ�SWD����
#define JTAG_SWD_Disable		0x00000100	//JTAG��SWD���ر�

/**********************************************************
                    λ��������غ궨��
              �ο���CM3Ȩ��ָ�ϡ���87 ~ 92ҳ
**********************************************************/

#define BITBAND(addr, bitnum)			((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)					*((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)			MEM_ADDR(BITBAND(addr, bitnum)) 

/**********************************************************
                       GPIO��ַӳ��
              ����ַ���ϼĴ���ƫ�Ƶ�ַ���
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
             ʵ�ֵ�һIO������������51��IO����
                   nֵҪС��IO������Ŀ
**********************************************************/ 

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

/**********************************************************
                     �ⲿ���ù��ܺ���
**********************************************************/

void STM32_Flash_Capacity(uint8_t *STMCapa);	//��ȡоƬ��������

void STM32_CPUID(uint8_t *IDbuff);	//��ȡCPUID

void STM_Clock_Init(uint8_t pll);	//ϵͳʱ�ӳ�ʼ��

void MY_NVIC_SetVectorTable(uint32_t NVIC_VectTab,uint32_t Offset);	//����������ƫ�Ƶ�ַ

void MY_NVIC_PriorityGroup_Config(uint32_t NVIC_PriorityGroup);	//�����жϷ���

void MY_NVIC_Init(uint8_t NVIC_PreemptionPriority,uint8_t NVIC_Subpriority,uint8_t NVIC_Channel,uint32_t NVIC_Group);


void MY_RCC_DeInit(void);	//����ʱ�ӼĴ�����λ

void SYS_Standby(void);	//����оƬ�������ģʽ

void SYS_SoftReset(void);	//ϵͳ��λ

void STM_JTAG_Set(uint32_t mode);	//JTAGģʽ����


uint8_t BCD_to_HEX(uint8_t BCD_Data);	//BCD��תΪHEX

uint8_t HEX_to_BCD(uint8_t HEX_Data);	//HEX��תΪBCD

uint16_t DX_to_HX(uint16_t DX_Data);	//10������תΪ16����

uint16_t HX_to_DX(uint16_t HX_Data);	//16������תΪ10����


void STM32_GPIOx_Init(
                        uint32_t RCC_APB2Periph,		/* GPIO��Ӧʱ�� */
						GPIO_TypeDef* GPIOx,			/* ����Ӧ��GPIO�� */
						uint16_t GPIO_Pinx,				/* GPIO��Ӧ�Ĺܽź� */
						GPIOSpeed_TypeDef GPIO_SPEED,	/* GPIO��ת�ٶ� */
						GPIOMode_TypeDef GPIO_MODE		/* GPIO����ģʽ */
					   );


//void Sqlist_Init(Sqlist *LIST);	//��ʼ�������б�
//void Sqlist_DeInit(void);	//��λ�����б�
//void InsertElem(Sqlist *L,uint16_t i,ElemType item);	//��һ����̬�������б����һ��Ԫ��


#endif

