//
// Created by liu on 2017/11/28.
//

#ifndef CPPTEST_CONTENTKEY_H
#define CPPTEST_CONTENTKEY_H

#include "Key.h"

class ContentKey : public Key {
public:
    ContentKey(const KeyPlace &rc_place, const ExactPlace &xy_place) : Key(rc_place, xy_place) {}
		ContentKey(const char r, const char c, const float x,  const float y) : Key(r,c,x,y) {}
    virtual void whenKeyDown(KeyState &ks);
		virtual void keepDown(KeyState &ks);
};


#endif //CPPTEST_CONTENTKEY_H
