#include "led.h"
void NOP(void) 
{  
  uint16_t i;  
  for (i = 0; i < 20; i++);  
}  
//PA8 OE
//PA9 MR 
//PB13 SCLK
//PB12 RCK
//PB15 MOSI
//LED IO��ʼ��
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA,PB�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;				 //PA8,PA9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8,9

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;	    		 //PB12\13\15 �˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	
	OE=1;NOP();
	MR=0;NOP();		
	OE=1;NOP();
	MOSI=0;NOP();
	RCK=0;NOP();
	SCLK=0;NOP();
	OE=0;NOP();
	MR=1;NOP();	
}



void HC595SendData(uint32_t SendVal)  
{ 
	uint8_t i; 
  for (i = 0; i < 24; i++)  
  {  
    if (((SendVal << i) & 0x800000) != 0 ) 
			MOSI=1;
    else 
			MOSI=0;
  
    SCLK=0; 
    NOP();  
    SCLK=1; 
  }  
  RCK=0;
  NOP();  
  RCK=1;  
}
