//
// Created by liu on 2017/11/28.
//

#ifndef CPPTEST_COMPOSITEKEY_H
#define CPPTEST_COMPOSITEKEY_H

#include "Key.h"
#include "Const.h"

/**
 * 此类表示 Ctrl，Alt，Shift 三键操作
 * 主要通过
 */
class CompositeKey : public Key {
public:
    CompositeKey(const KeyPlace &rc_place, const ExactPlace &xy_place, const char composite_bit):
            Key(rc_place, xy_place), compositeByte(composite_bit) {}
	
		CompositeKey(const char r, const char c, const float x,  const float y, const char composite_bit):
            Key(r,c,x,y), compositeByte(composite_bit) {}
    virtual void beforeAllProcess(KeyState &ks);

    /**
     * @brief 监测到该键按下时调用，修改ks中composite标志
     * @param ks
     */
    virtual void whenKeyDown(KeyState &ks);
    /**
     * @brief 所有键按下之后的后处理
     * @details 用于将未确定的键自动降层到 大层(8小层的倍数) + 自身的组合键
     * 例如：
     *  ctrl + shift + 左
     *  按下时
     *  情况1，应该在(ctrl | shift)的mini层上发送左键盘码。
     *  情况2，如果shift + 左 被定义为 a，则该发送 ctrl + a 键盘码。
     * 此函数操作为，对每个未确定的按键：
     *  1. 去掉this(假设为ctrl)键，是定义的键码（对应情况2）=> 相应键码加入发送队列
     *  2. 去掉this(假设为ctrl)键，还不是键码（对应情况1）=> 修改未确定队列中的元素
     * @param ks
     */
    virtual void afterAllProcess(KeyState &ks);

private:
    char compositeByte; ///> 组合位，设置成 1 2 4 之类
};


#endif //CPPTEST_COMPOSITEKEY_H
