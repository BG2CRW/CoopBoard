/**********************************************************
* @ File name -> key.c
* @ Version   -> V1.0
* @ Date      -> 01-18-2014
* @ Brief     -> 按键驱动函数

 V1.*
* @ Revise    ->
**********************************************************/

#include "key.h"

/**********************************************************
* 函数功能 ---> KEY接口初始化
* 入口参数 ---> none
* 返回参数 ---> none 
* 功能说明 ---> none
**********************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ROW1\2\3\4\5\6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //??PC0?PC5????????11110->11101->11011->10111->01111->11110
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//COL1\2\3\4\5\6\7\8\9\10\11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //??PB0\1\3\4\5\6\7\8\9\10\11????
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//COL12\13\14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //??PC6\7\8?????
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
}



u8 KEY_Scan(u8 mode)
{
	static u8 key_loo=1;	//按键松开标志
	if(mode)	key_loo = 1;	//按键松开
	if(key_loo && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 1))	//按键按下
	{					
		delay_ms(10);	//延时消抖动
        key_loo = 0;
             if(KEY0 == 0)	return KEY_LEFT;
        else if(KEY1 == 0)	return KEY_UP;
        else if(KEY2 == 0)  return KEY_DOWN;
        else if(KEY3 == 0)  return KEY_RIGHT;
		else if(KEY4 == 1)	return KEY_WKUP;
	}
	else if(KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 0)	key_loo = 1;	//按键已经释放	
		
	return 0;

}
 
