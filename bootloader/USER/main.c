#include "stm32_config.h"
#include "key.h"


#include "hw_config.h"	//USB���ͷ�ļ�
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
                           ������
**********************************************************/
int main(void)
{
	delay_init(72);	//��ʼ����ʱ����
	USART1_Init(9600);	//��ʼ������1
	KEY_Init();
	ROW1=0;
	DFU_Button_Config();	//��ʼ����תAPP���򰴼�

	//����Ƿ����DFUģʽ����������û�а�������ת��APP������ִ��
	if(DFU_Button_Read() == 1)//enter APP
	{
		if(((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)	//���APP��ַ�Ƿ�Ϸ�
		{
			//��ת��APP��ַ��ʼִ�У���ַ+4λ���Ǹ�λ�ж����
			JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
			Jump_To_Application = (pFunction) JumpAddress;

			//����APP�����ջָ��
			__set_MSP(*(__IO uint32_t*) ApplicationAddress);
			
			//��ת��APP������ִ��
			Jump_To_Application();
		}
	}
	if(DFU_Button_Read() == 0)//enter DFU
	{
	
	}
	//�����Ѿ����£������APP����ģʽ
	DeviceState = STATE_dfuERROR;
	DeviceStatus[0] = STATUS_ERRFIRMWARE;
	DeviceStatus[4] = DeviceState;
	
	Set_System();
	Set_USBClock();
	USB_Init();
	
	while(1);
} 
