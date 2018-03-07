//
// Created by liu on 2017/11/28.
//

#include "CompositeKey.h"

void CompositeKey::beforeAllProcess(KeyState &ks) {
    Key::beforeAllProcess(ks);
    if(ks.isDown(rc_place.getRow(), rc_place.getCol())) {
        ks.composite_mark |= this->compositeByte;
    }
}

void CompositeKey::whenKeyDown(KeyState &ks) {
    // do nothing
}

void CompositeKey::afterAllProcess(KeyState &ks) {
		if(
			ks.isDown(rc_place.getRow(), rc_place.getCol())
			&&
			ks.code_to_send.size() == 0
		) {
        ks.code_to_send.push_back(KeyCode(0, this->compositeByte));
    }
}

