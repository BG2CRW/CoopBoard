//
// Created by liu on 2017/11/30.
//

#ifndef CPPTEST_DEFINEKEY_H
#define CPPTEST_DEFINEKEY_H

#include "Key.h"
#include "CompositeKey.h"
#include "ContentKey.h"
#include "FunctionKey.h"

typedef ContentKey KK;
typedef CompositeKey CK;
typedef FunctionKey FK;
#define DefK(KT, r, c, x, y, args...) do { Key::setKey(r, c, new KT(r, c, x, y, ##args));} while(0)

void define_key() {
    Key::keyboardClear();
    DefK(CK, 2, 0, 0, 0, KB_SHIFT); // shift
		DefK(CK, 3, 0, 0, 0, KB_CTRL); // ctrl  
		DefK(CK, 3, 2, 0, 0, KB_ALT); // alt
		DefK(CK, 3, 3, 0, 0, KB_WIN); // command
    DefK(FK, 2, 1, 0, 0, 1); // fn1
    DefK(FK, 3, 1, 0, 0, 2); // fn2
    DefK(FK, 3, 4, 0, 0, 3); // fn3
    DefK(FK, 3, 8, 0, 0, 4); // fn4
    //DefK(FK, 2, 13, 0, 0, 5); // fn5
    // define other keys as ContentKey
    for (char i = 0; i < MAX_ROW; ++i) {
        for (char j = 0; j < ROW_LENGTH[i]; ++j) {
            if (!Key::getKey(i, j)) {
                Key::setKey(i, j, new KK(i, j, 0, 0));
            }
        }
    }
}

#endif //CPPTEST_DEFINEKEY_H
