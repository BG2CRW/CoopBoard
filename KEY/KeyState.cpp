//
// Created by liu on 2017/11/28.
//

#include "KeyState.h"

KeyState::KeyState() : fn_layer(0), composite_mark(0) {
    for (int i = 0; i < MAX_ROW; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            origin[i][j] = false;
        }
    }
}

bool KeyState::isDown(const unsigned char row, const unsigned char col)  {
    return origin[row][col];
}

bool KeyState::sameOrigin(bool o[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < MAX_ROW; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            if (o[i][j] != origin[i][j]) return false;
        }
    }
    return true;
}

void KeyState::copyOrigin(bool (*o)[14]) {
    for (int i = 0; i < MAX_ROW; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            o[i][j] = isDown(i, j);
        }
    }
}

