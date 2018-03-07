#ifndef __LED_H
#define __LED_H	 

#ifdef __cplusplus
 extern "C" {
#endif 

#include "sys.h"

//PA8 OE,PA9 MR PB13 SCLK,PB12 RCK,PB15 MOSI
#define OE PAout(8)	// PA8
#define MR PAout(9)	// PA9
#define RCK PBout(12)	//PB12
#define SCLK PBout(13)	//PB13
#define MOSI PBout(15)	//PB15	 

void LED_Init(void);//≥ı ºªØ
void HC595SendData(uint32_t SendVal);	 

#ifdef __cplusplus
}
#endif
		 				    
#endif
