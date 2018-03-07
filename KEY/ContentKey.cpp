//
// Created by liu on 2017/11/28.
//

#include "ContentKey.h"

void ContentKey::whenKeyDown(KeyState &ks) {
    unsigned int mini_layer = ks.getMiniLayer();
    unsigned char raw = rc_place.getRow();
    unsigned char col = rc_place.getCol();
    // 查看是否可以直接生成传送键码，否则对降层，尝试其他键码
    if (codeMap->isSendable(mini_layer, raw, col)) {
        ks.code_to_send.push_back(codeMap->getKeyCode(mini_layer, raw, col));
    } else if(mini_layer & 15) { // 如果是因为miniLayer中导致的没有键码，则自动判断
        // 尝试去掉一些composite键，查找键码
        static const unsigned char mark[] = {/*去掉一个*/1, 2, 4, 8, /*去掉两个*/3, 5, 6, 9, 10, 12, /*去掉三个*/7, 11, 13, 14,  15};
        for (int j = 0; j < sizeof(mark); ++j) {
            unsigned char composite = (unsigned char)mini_layer & mark[j];
            if (!composite) continue; // 没有按下该位的composite键
            if (codeMap->isSendable(mini_layer - composite, raw, col)) {
                KeyCode code = codeMap->getKeyCode(mini_layer - composite, raw, col);
                code.setComposite(code.getComposite() | composite);
                ks.code_to_send.push_back(code);
                return;
            }
            // 如果在mini层找不到，就不会做任何动作了
        }
    }
}

void ContentKey::keepDown(KeyState &ks) { // 按下时，在跳沿监测结束后
    Key::keepDown(ks);
    ContentKey::whenKeyDown(ks);
}
