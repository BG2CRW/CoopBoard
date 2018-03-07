//
// Created by liu on 2017/11/30.
//

#ifndef CPPTEST_DEFINEKEYLAYER_H
#define CPPTEST_DEFINEKEYLAYER_H

#include "Const.h"
#include "KeyCodeStanderd.h"
#include "KeyCode.h"

///???
typedef KeyCode C;
KeyCode layer0[MAX_ROW][MAX_COL] =
{ // layer 0 default
// row 1
	{C(KB_TAB), C(KB_Q), C(KB_W), C(KB_E), C(KB_R), C(KB_T), C(KB_Y), C(KB_U), C(KB_I), C(KB_O), C(KB_P), C(KB_LEFT_BRACKET), C(KB_RIGHT_BRACKET), C(KB_DEL)},
// row 2
	{C(KB_CAPSLOCK), C(KB_A), C(KB_S), C(KB_D), C(KB_F), C(KB_G), C(KB_H), C(KB_J), C(KB_K), C(KB_L), C(KB_SEMICOLON), C(KB_QUOTES), C(KB_RETURN)},
// row 3
	{C(), C(), C(KB_Z), C(KB_X), C(KB_C), C(KB_V), C(KB_B), C(KB_N), C(KB_M), C(KB_COMMA), C(KB_END_MARK), C(KB_SLASH), C(KB_UP_ARROW), C(KB_DELETE_FORWARD)},
// row 4
	{C(), C(), C(), C(), C(), C(KB_SPACE), C(KB_SPACE), C(KB_RIGHT_CLICK), C(), C(KB_LEFT_ARROW), C(KB_DOWN_ARROW), C(KB_RIGHT_ARROW)},
};
KeyCode minilayer1[MAX_ROW][MAX_COL] =
{ // layer 0 default ctrl      
// row 1
	{},
// row 2
	{},
// row 3
	{C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(KB_BACK_SLASH), C(), C()},
};
KeyCode layer1[MAX_ROW][MAX_COL] =     
{ // layer 8 f1 number mini board implement
// row 1  Q    W    E    R        T        Y        U    I    O    P    [                   ]                    DEL
	{C(KB_BACK_QUOTES), C(KB_1), C(KB_2), C(KB_3), C(KB_4), C(KB_5), C(KB_6), C(KB_7), C(KB_8), C(KB_9), C(KB_0), C(KB_MINUS), C(KB_EQUAL), C(KB_DEL)},
// row 2  A    S    D    F        G        H        J    K    L    ;                '             ENTER
	{C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(KB_QUOTES), C(KB_RETURN)},
// row 3  SHIFTZ    X    C    V        B        N        M                      ,<           .>                 /?           ^
	{C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(KB_BACK_SLASH), C(KB_PRT_SCR), C()},
// row 4  f3   f4   CTRL ALT  SPACE1   SPACE2       f5   CTRL <                 v                 >
	{C(), C(), C(), C(), C(), C(KB_SPACE), C(KB_SPACE), C(), C(), C(KB_VOLUME_UP), C(KB_VOLUME_MUTE), C(KB_VOLUME_DOWN)},
};
KeyCode layer2[MAX_ROW][MAX_COL] =
{ // layer 2 f2 F1-F12 Layer [function keys]
// row 1        Q         W         E         R         T         Y         U         I         O         P          [          ]          DEL
	{C(KB_ESC), C(KB_F1), C(KB_F2), C(KB_F3), C(KB_F4), C(KB_F5), C(KB_F6), C(KB_F7), C(KB_F8), C(KB_F9), C(KB_F10), C(KB_F11), C(KB_F12), C(KB_DEL)},
// row 2  A    S    D    F    G    H    J    K    L    ;    '    ENTER
	{C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(KB_RETURN)},
// row 3  SHIFTZ    X    C    V    B    N    M    ,<   .>   /?   ^               f6
	{C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(KB_UP_ARROW), C()},
// row 4  f3   f4   CTRL ALT  SPACE1   SPACE2       f5   CTRL <                 v                 >
	{C(), C(), C(), C(), C(), C(KB_0), C(KB_SPACE), C(), C(), C(KB_LEFT_ARROW), C(KB_DOWN_ARROW), C(KB_RIGHT_ARROW)},
};
KeyCode layer3[MAX_ROW][MAX_COL] =
{ // layer 3 f3 HOME END INSERT DELETE ... [control keys]
// row 1  Q    W    E    R    T    Y    U              I                  O            P    [    ]    DEL
	{C(135), C(136), C(137), C(138), C(139), C(140), C(141), C(142), C(143), C(144), C(145), C(146), C(147), C(148)},
// row 2  A    S    D    F    G    H    J    		  K    L    ;    '    ENTER
	{C(149), C(150), C(151), C(152), C(153), C(154), C(155), C(156), C(157), C(158), C(159), C(160), C(161)},
// row 3  SHIFTZ    X    C    V    B    N    M    ,<   .>   /?   ^               f6
	{C(), C(), C(162), C(163), C(164), C(165), C(166), C(167), C(168), C(169), C(170), C(171), C(172), C(173)},
// row 4  f3   f4   CTRL ALT  SPACE1       SPACE2       f5   CTRL <                 v                 >
	{C(), C(), C(), C(), C(), C(174), C(175), C(176), C(), C(177), C(178), C(179)},
};
KeyCode layer4[MAX_ROW][MAX_COL] =
{ // layer 4 f4
// row 1
// row 1                        Q         W         E         R         T         Y         U         I         O         P          [          ]          DEL
	{C(KB_BACK_QUOTES, KB_SHIFT), C(KB_1, KB_SHIFT), C(KB_2, KB_SHIFT), C(KB_3, KB_SHIFT), C(KB_4, KB_SHIFT), C(KB_5, KB_SHIFT), C(KB_6, KB_SHIFT), C(KB_7, KB_SHIFT), C(KB_8, KB_SHIFT), C(KB_9, KB_SHIFT), C(KB_0, KB_SHIFT), C(KB_MINUS, KB_SHIFT), C(KB_EQUAL, KB_SHIFT), C(KB_DEL)},
// row 2              A        S        D        F        G        H        J        K        L        ;        '    ENTER
	{C(KB_BACK_QUOTES), C(KB_1), C(KB_2), C(KB_3), C(KB_4), C(KB_5), C(KB_6), C(KB_7), C(KB_8), C(KB_9), C(KB_0), C(KB_MINUS), C(KB_EQUAL)},
// row 3  SHIFTZ    X    C    V    B    N    M    ,<   .>   /?   ^               f6
	{C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(), C(KB_UP_ARROW), C()},
// row 4  f3   f4   CTRL ALT  SPACE1       SPACE2       f5   CTRL <                 v                 >
	{C(), C(), C(), C(), C(), C(KB_SPACE), C(KB_SPACE), C(), C(), C(KB_LEFT_ARROW), C(KB_DOWN_ARROW), C(KB_RIGHT_ARROW)},
};

/*KeyCode layer5[MAX_ROW][MAX_COL] =
{ // layer 5 f5
// row 1
	{C(KB_TAB)}
};*/

void define_key_layer(CodeMap* codeMap) {
  codeMap->setLayer(0, layer0);
	codeMap->setMiniLayer(0, KB_CTRL, minilayer1);
	codeMap->setLayer(1, layer1);
	codeMap->setLayer(2, layer2);
	codeMap->setLayer(3, layer3);
	codeMap->setLayer(4, layer4);
	//codeMap->setLayer(5, layer5);
}

#endif //CPPTEST_DEFINEKEYLAYER_H
