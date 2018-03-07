//
// Created by liu on 2017/11/28.
//
#ifdef __cplusplus
extern "C" {
#endif 

#include "delay.h"
#include "sys.h"

#ifdef __cplusplus
}
#endif

#include "Key.h"
#include "tool.h"

CodeMap* Key::codeMap;
Key* Key::keyboard[MAX_ROW * MAX_COL];

void Key::KEY_Init(void) //初始化矩阵键盘要使用的GPIO口。
{	
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ROW1\2\3\4\5\6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //定义PC0到PC5为推挽输出、、。11110->11101->11011->10111->01111->11110
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//COL1\2\3\4\5\6\7\8\9\10\11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //定义PB0\1\3\4\5\6\7\8\9\10\11上拉输入
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//COL12\13\14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //定义PC6\7\8为上拉输入
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}


void Key::updateCOL(bool* col)
{
	col[0]=!COL1;
	col[1]=!COL2;
	col[2]=!COL3;
	col[3]=!COL4;
	col[4]=!COL5;
	col[5]=!COL6;
	col[6]=!COL7;
	col[7]=!COL8;
	col[8]=!COL9;
	col[9]=!COL10;
	col[10]=!COL11;
	col[11]=!COL12;
	col[12]=!COL13;
	col[13]=!COL14;	
}
void disable(unsigned char* col) {
	for (int i = 0; i < MAX_COL; i++) {
		col[i] = 0;
	}
}

void Key::scanKeys(KeyState & ks) {
	
//	disable(ks.origin[0]);
//	disable(ks.origin[1]);
//	disable(ks.origin[2]);
//	disable(ks.origin[3]);
	//让row1到row6输出二进制的011111.
	ROW1=0; ROW2=1; ROW3=1; ROW4=1; ROW5=1; ROW6=1;
	delay_us(10);
	updateCOL(ks.origin[0]);
	ROW1=1; ROW2=0; ROW3=1; ROW4=1; ROW5=1; ROW6=1;
	delay_us(10);
	updateCOL(ks.origin[1]);
	ROW1=1; ROW2=1; ROW3=0; ROW4=1; ROW5=1; ROW6=1;
	delay_us(10);
	updateCOL(ks.origin[2]);
	ROW1=1; ROW2=1; ROW3=1; ROW4=0; ROW5=1; ROW6=1;
	delay_us(10);
	updateCOL(ks.origin[3]);
}


void Key::decodeKeyCode(KeyState & ks) {
		static bool pre_ks[MAX_ROW][MAX_COL];
		static char pre_fn_layer; // 这是为了做一个fn层切换延迟，防止误触的。
		if (ks.sameOrigin(pre_ks)) {
			return;
		}

    for (int i = 0; i < MAX_ROW; ++i) {
        for (int j = 0; j < ROW_LENGTH[i]; ++j) {
            if (keyboard[i * MAX_COL + j]) keyboard[i * MAX_COL + j]->beforeAllProcess(ks);
        }
    }

    for (int i = 0; i < MAX_ROW; ++i) {
        for (int j = 0; j < ROW_LENGTH[i]; ++j) {
            if (keyboard[i * MAX_COL + j]) {
                if (ks.isDown(i, j) && pre_ks[i][j]) {
					keyboard[i * MAX_COL + j]->keepDown(ks);
                } else if (!ks.isDown(i, j) && !pre_ks[i][j]) {
					keyboard[i * MAX_COL + j]->keepUp(ks);
                }
            }
        }											
    }
		// 挑檐信息更重要，放在之后处理。键码之后的更重要。
		for (int i = 0; i < MAX_ROW; ++i) {
			for (int j = 0; j < ROW_LENGTH[i]; ++j) {
				if (keyboard[i * MAX_COL + j]) {
					if (ks.isDown(i, j) && !pre_ks[i][j]) {
						keyboard[i * MAX_COL + j]->whenKeyDown(ks);
					} else if (!ks.isDown(i, j) && pre_ks[i][j]) {
						keyboard[i * MAX_COL + j]->whenKeyUp(ks);
					}
				}
			}
		}

    for (int i = 0; i < MAX_ROW; ++i) {
        for (int j = 0; j < ROW_LENGTH[i]; ++j) {
            if (keyboard[i * MAX_COL + j]) {
				keyboard[i * MAX_COL + j]->afterAllProcess(ks);
            }
        }
    }
    for (int i = 0; i < MAX_ROW; ++i) {
        for (int j = 0; j < ROW_LENGTH[i]; ++j) {
            if (keyboard[i * MAX_COL + j]) {
				keyboard[i * MAX_COL + j]->beforeKeyCodeSend(ks);
            }
        }
    }
		
		if (pre_fn_layer > ks.fn_layer) {
			// 逻辑是在fn下降层数之后（抬起按键）。总是等待一段时间再检测，防止其他被组合的按键没有抬起来。
			delay_ms(100);
			pre_fn_layer = ks.fn_layer;
			return;
		}
		tool::sent_key_code(ks.code_to_send);
		ks.copyOrigin(pre_ks);
		pre_fn_layer = ks.fn_layer;
}
