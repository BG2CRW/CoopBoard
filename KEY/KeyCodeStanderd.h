//
// Created by liu on 2017/11/28.
//

#ifndef CPPTEST_KEYCODESTANDERD_H_H
#define CPPTEST_KEYCODESTANDERD_H_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "sys.h"	 
#define ROW1 PCout(0)	// PC0
#define ROW2 PCout(1)	// PC1		 
#define ROW3 PCout(2)	// PC2
#define ROW4 PCout(3)	// PC3	
#define ROW5 PCout(4)	// PC4
#define ROW6 PCout(5)	// PC5	

#define COL1 PBin(0);
#define COL2 PBin(1);
#define COL3 PBin(3);
#define COL4 PBin(4);
#define COL5 PBin(5);
#define COL6 PBin(6);
#define COL7 PBin(7);
#define COL8 PBin(8);
#define COL9 PBin(9);
#define COL10 PBin(10);
#define COL11 PBin(11);
#define COL12 PCin(6);
#define COL13 PCin(7);
#define COL14 PCin(8);

#ifdef __cplusplus
}
#endif

#define KB_NULL  0
#define KB_RESERVED 0
#define KB_ErrorRollOver 1
#define KB_POSTFail  2
#define KB_ErrorUndefined  3
#define KB_A  4
#define KB_B 5
#define KB_C 6
#define KB_D 7
#define KB_E 8
#define KB_F 9
#define KB_G 10
#define KB_H 11
#define KB_I 12
#define KB_J 13
#define KB_K 14
#define KB_L 15
#define KB_M 16
#define KB_N 17
#define KB_O 18
#define KB_P 19
#define KB_Q 20
#define KB_R 21
#define KB_S 22
#define KB_T 23
#define KB_U 24
#define KB_V 25
#define KB_W 26
#define KB_X 27
#define KB_Y 28
#define KB_Z 29
#define KB_1 30
#define KB_2 31
#define KB_3 32
#define KB_4 33
#define KB_5 34
#define KB_6 35
#define KB_7 36
#define KB_8 37
#define KB_9 38
#define KB_0 39
#define KB_RETURN 40
#define KB_ESC 41
#define KB_DEL 42
#define KB_TAB 43
#define KB_SPACE 44
#define KB_MINUS 45
#define KB_EQUAL 46
#define KB_LEFT_BRACKET 47
#define KB_RIGHT_BRACKET 48
#define KB_BACK_SLASH 49
#define KB_SEMICOLON 51 // ; :
#define KB_BACK_QUOTES 53//·~
#define KB_QUOTES 52 // " '
#define KB_COMMA 54
#define KB_END_MARK 55
#define KB_SLASH 56
#define KB_CAPSLOCK 57
#define KB_F1 58
#define KB_F2 59
#define KB_F3 60
#define KB_F4 61
#define KB_F5 62
#define KB_F6 63
#define KB_F7 64
#define KB_F8 65
#define KB_F9 66
#define KB_F10 67
#define KB_F11 68
#define KB_F12 69
#define KB_PRT_SCR 70
#define KB_SCROLL_LOCK 71
#define KB_PAUSE 72
#define KB_INSERT 73
#define KB_HOME 74
#define KB_PAGE_UP 75
#define KB_DELETE_FORWARD 76
#define KB_END 77
#define KB_PAGE_DOWN 78
#define KB_RIGHT_ARROW 79
#define KB_LEFT_ARROW 80
#define KB_DOWN_ARROW 81
#define KB_UP_ARROW 82
#define KB_RIGHT_CLICK 101
#define KB_VOLUME_MUTE 127
#define KB_VOLUME_UP 128
#define KB_VOLUME_DOWN 129
//// 以下不属于标准键盘标准       
//#define KB_FN1 101                      
//#define KB_FN2 102
//#define KB_FN3 103
//#define KB_FN4 104
//#define KB_FN5 105

// 以下三个按键在八字节的第一个字节的0123位
#define KB_CTRL 1  //D0
#define KB_SHIFT 2 //D1
#define KB_ALT 4  //D2
#define KB_WIN 8  //D4

//第二个字节为0
//第345678字节保存键值

#endif //CPPTEST_KEYCODESTANDERD_H_H
