//
// Created by liu on 2017/11/28.
//

#ifndef CPPTEST_KEYCODE_H
#define CPPTEST_KEYCODE_H

#include <utility>
#include <vector>
#include "Const.h"
#include <stdio.h>

class KeyCode {
public:
    KeyCode(unsigned char code = 0, unsigned char composite = 0) : composite(composite), code(code) {}
	KeyCode(const KeyCode& that) : composite(that.composite), code(that.code) {}
    bool isSendable()const { return (bool)(code | composite); }
    unsigned char getComposite() const { return composite; }
    void setComposite(unsigned char composite) { KeyCode::composite = composite; }
    unsigned char getCode() const { return code; }
    void setCode(unsigned char code) { KeyCode::code = code; }

private:
    unsigned char composite;
    unsigned char code;
};

class CodeLayer {
public:
    CodeLayer() { // 这个函数保证不被设置的空layer中没有元素
			codes = NULL;
		}
    KeyCode getCode(unsigned char row, unsigned char col) const;
	void setCodes(KeyCode layer[MAX_ROW][MAX_COL]);
	void clear() {codes=NULL;}
private:
    KeyCode (*codes)[MAX_COL];

};

class CodeMap {
public:
    CodeMap() {}
    bool isSendable(unsigned int mini_layer, unsigned char row, unsigned char col);
	void setLayer(unsigned int big_layer_index, KeyCode layer[MAX_ROW][MAX_COL]);
	void setMiniLayer(unsigned int big_layer_index, unsigned char layer_inner_index, KeyCode layer[MAX_ROW][MAX_COL]);
    KeyCode getKeyCode(unsigned int mini_layer, unsigned char row, unsigned char col);
    const CodeLayer &getLayer(const unsigned int i) const { return *layers[i]; }
	void resize(size_t n);
    static CodeMap *defaultCodeMap;
private:
    std::vector<CodeLayer*> layers;

};

#endif //CPPTEST_KEYCODE_H
