#include "stm32_config.h"
#include "key.h"


#include "hw_config.h"	//USB相关头文件
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_pwr.h"
#include "dfu_mal.h"

typedef  void (*pFunction)(void);

uint8_t DeviceState;
uint8_t DeviceStatus[6];
pFunction Jump_To_Application;
uint32_t JumpAddress;

/**********************************************************
                           主函数
**********************************************************/
int main(void)
{
	delay_init(72);	//初始化延时函数
	USART1_Init(9600);	//初始化串口1
	KEY_Init();
	ROW1=0;
	DFU_Button_Config();	//初始化跳转APP程序按键

	//检测是否进入DFU模式按键，开机没有按下则跳转到APP程序中执行
	if(DFU_Button_Read() == 1)//enter APP
	{
		if(((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)	//检测APP地址是否合法
		{
			//跳转到APP地址开始执行，地址+4位置是复位中断入口
			JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
			Jump_To_Application = (pFunction) JumpAddress;

			//设置APP程序堆栈指针
			__set_MSP(*(__IO uint32_t*) ApplicationAddress);
			
			//跳转到APP程序中执行
			Jump_To_Application();
		}
	}
	if(DFU_Button_Read() == 0)//enter DFU
	{
	
	}
	//按键已经按下，则进入APP升级模式
	DeviceState = STATE_dfuERROR;
	DeviceStatus[0] = STATUS_ERRFIRMWARE;
	DeviceStatus[4] = DeviceState;
	
	Set_System();
	Set_USBClock();
	USB_Init();
	
	while(1);
} 
