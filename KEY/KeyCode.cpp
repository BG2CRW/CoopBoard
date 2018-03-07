//
// Created by liu on 2017/11/28.
//

#include "KeyCode.h"
#include "KeyCodeStanderd.h"
#include "CompositeKey.h"
#include "vector"
void CodeLayer::setCodes(KeyCode layer[MAX_ROW][MAX_COL]) {
	codes = layer;
//	clear();
//	codes[3].resize(1);
//	std::vector<KeyCode *> s;
//	s.resize(4);
//	codes[2].resize(1);
//	codes[1].resize(1);
//	codes[0].resize(1);
//	
//	for (char i = 1; i < MAX_ROW; i++) {
//		for (int j = MAX_COL - 10; j >=0 && j < MAX_COL; j--) {
//            if (layer[i][j].isSendable()) {
////                if (codes[i].size() <= j) {
////                    codes[i].resize(j + 1);
////                }
//                codes[i].operator[](j) = new KeyCode(layer[i][j].getCode(), layer[i][j].getComposite());
//            }
//		}
//	}
}

KeyCode CodeLayer::getCode(unsigned char row, unsigned char col) const {
    if (row >= MAX_ROW || col >= MAX_COL || codes == NULL) {
        return KeyCode();
    } else {
        return codes[row][col];
    }
}

CodeMap * CodeMap::defaultCodeMap = new CodeMap();

bool CodeMap::isSendable(unsigned int mini_layer, unsigned char row, unsigned char col) {
    if (mini_layer >= layers.size()) {
        return false;
    }
    return layers[mini_layer]->getCode(row, col).isSendable();
}

void CodeMap::setLayer(unsigned int big_layer_index, KeyCode layer[MAX_ROW][MAX_COL])  {
    setMiniLayer(big_layer_index, 0, layer);
}

void CodeMap::setMiniLayer(unsigned int big_layer_index, unsigned char layer_inner_index, KeyCode layer[MAX_ROW][MAX_COL]) {
    unsigned int layer_index = (big_layer_index << COMPOSITE_KEY_NUM) + layer_inner_index;
    if (layers.size() <= layer_index) resize(layer_index + 1);
    layers[layer_index]->setCodes(layer);
}

KeyCode CodeMap::getKeyCode(unsigned int mini_layer, unsigned char row, unsigned char col) {
    if (mini_layer >= layers.size()) {
        KeyCode empty_code;
        return empty_code;
    } else {
        return layers[mini_layer]->getCode(row, col);
    }

}

void CodeMap::resize(size_t n) {
    int old = layers.size();
    layers.resize(n);
    for (int i = old; i < n; ++i) {
        layers[i] = new CodeLayer;
    }
}
