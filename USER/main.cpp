#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "Key.h"
#include "ContentKey.h"
#include "CompositeKey.h"
#include "FunctionKey.h"
#include "led.h"
#include "usb_lib.h"
#include "usb_pwr.h" 
#include <vector>
#include "DefineKey.h"
#include "DefineKeyLayer.h"
unsigned char result;
int main(void)
{ 
	SCB->VTOR = FLASH_BASE | 0X30000; /* Vector Table Relocation in Internal FLASH. */
	delay_init();	//延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组设置	 
	uart_init(9600);//串口初始化为9600
	LED_Init();		//初始化与LED连接的硬件接口
	HC595SendData(0xff0000);
	Key::KEY_Init();	//按键初始化		 	      						    	   
  delay_ms(500);
	USB_Port_Set(0); 	//USB先断开
	delay_ms(300);
  USB_Port_Set(1);	//USB再次连接
	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	        			
	delay_ms(500);
	define_key();
  define_key_layer(CodeMap::defaultCodeMap);
  Key::setCodeMap(CodeMap::defaultCodeMap);
 	while(1)
	{	  
		HC595SendData(0xff0000);
		KeyState ks;
		Key::scanKeys(ks);
		Key::decodeKeyCode(ks);
	}		                          
}
