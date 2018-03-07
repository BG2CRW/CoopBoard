//
// Created by liu on 2017/11/28.
//

#include "FunctionKey.h"


void FunctionKey::beforeAllProcess(KeyState &ks) {
    Key::beforeAllProcess(ks);
    if(ks.isDown(rc_place.getRow(), rc_place.getCol())) {
        ks.fn_layer = this->layer;
    }
}
