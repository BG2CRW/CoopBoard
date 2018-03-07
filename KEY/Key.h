//
// Created by liu on 2017/11/28.
//

#ifndef CPPTEST_KEY_H
#define CPPTEST_KEY_H

#include "KeyState.h"
#include "KeyCode.h"
#include "KeyCodeStanderd.h"
#include "Const.h"

class Key {
public:
    Key(const KeyPlace &rc_place, const ExactPlace &xy_place) :
        rc_place(rc_place), xy_place(xy_place) {}
	Key(const char * a, const float * b) : rc_place(a[0], a[1]), xy_place(b[0], b[1]) {}
	Key(const char r, const char c, const float x,  const float y) : rc_place(r, c), xy_place(x, y) {}
    static void KEY_Init(void);
    static void updateCOL(bool* col);
    static void scanKeys(KeyState & ks);
    static void decodeKeyCode(KeyState & ks);
    virtual void whenKeyDown(KeyState & ks) {};
    virtual void whenKeyUp(KeyState & ks) {};
	virtual void keepDown(KeyState &ks) {};
	virtual void keepUp(KeyState &ks) {};
    virtual void beforeAllProcess(KeyState & ks) {};
    virtual void afterAllProcess(KeyState & ks) {};
    virtual void beforeKeyCodeSend(KeyState & ks) {};

    // 此方法不传递所有权
    static void setCodeMap(CodeMap * codeMap) { Key::codeMap = codeMap; }
    static void setKey(char i, char j, Key * kp) { keyboard[i * MAX_COL + j] = kp;}
    static Key* getKey(char i, char j) { return keyboard[i * MAX_COL + j]; }
	static void keyboardClear() { for (int i = 0; i < MAX_ROW * MAX_COL; ++i) { delete keyboard[i]; keyboard[i] = NULL; }}
protected:
    KeyPlace rc_place;
    ExactPlace xy_place;
    static CodeMap* codeMap;
    static Key* keyboard[MAX_ROW * MAX_COL];
};


#endif //CPPTEST_KEY_H
