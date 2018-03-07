//
// Created by liu on 2017/11/28.
//

#ifndef CPPTEST_FUNCTIONKEY_H
#define CPPTEST_FUNCTIONKEY_H

#include "Key.h"

class FunctionKey : public Key{
public:
    FunctionKey(const KeyPlace &rc_place, const ExactPlace &xy_place, const unsigned char layer):
            Key(rc_place ,xy_place), layer(layer) {}
		FunctionKey(const char r, const char c, const float x,  const float y, const unsigned char layer) : Key(r,c,x,y), layer(layer) {}

    virtual void beforeAllProcess(KeyState &ks);

private:
    unsigned char layer;
};


#endif //CPPTEST_FUNCTIONKEY_H
