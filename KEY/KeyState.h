//
// Created by liu on 2017/11/28.
//

#ifndef CPPTEST_KEYSTATE_H
#define CPPTEST_KEYSTATE_H

#include "KeyCode.h"
#include "Const.h"

struct KeyPlace {
public:
    KeyPlace(char row, char col) : row(row), col(col) {}
		KeyPlace(char * rc) : row(rc[0]), col(rc[1]) {}
		KeyPlace(const KeyPlace& that) : row(that.row), col(that.col) {}
    unsigned char getRow() const { return row; }
    unsigned char getCol() const { return col; }
    void setRow(unsigned char row) { KeyPlace::row = row; }
    void setCol(unsigned char col) { KeyPlace::col = col; }
private:
    unsigned char row, col;
};

struct ExactPlace {
public:
    ExactPlace(float x, float y) : x(x), y(y) {}
		ExactPlace(float * xy) : x(xy[0]), y(xy[1]) {}
		ExactPlace(const ExactPlace & that) : x(that.x), y(that.y) {}
    float getX() const { return x; }
    void setX(float x) { ExactPlace::x = x; }
    float getY() const { return y; }
    void setY(float y) { ExactPlace::y = y; }
private:
    float x,y;
};

/**
 * \brief 此类用于存放按下键位的原始状态并在键之间传递，使得形成最终的键码。
 */
class KeyRemainDeloy {
public:
    KeyRemainDeloy(unsigned int miniLayer,
                   unsigned char raw,
                   unsigned char col,
                   unsigned char compositeMark = 0)
            : miniLayer(miniLayer), raw(raw), col(col), compositeMark(compositeMark) {}

    unsigned int miniLayer;
    unsigned char raw, col;
    unsigned char compositeMark;
};

/**
 * \brief 此类用于保存状态，供Key之间处理并确定最终发送的键码
 * \details
 * 对象的声明周期为：
 *  键盘扫描完成后
 *      1. 生成
 *      2. 传入预处理程序
 *      3. 传入每个键盘处理
 *      4. 传入后处理程序
 *      5. 传入发送前循环处理程序
 *      6. 传入键码发送程序发送键码
 *      7. 销毁
 */
class KeyState {
public:
	KeyState();
    bool isDown(const unsigned char row, const unsigned char col);
    void setData(const unsigned char row, const unsigned char col, bool isDown) {
        origin[row][col] = isDown;
    }

    unsigned int getMiniLayer() {
        return (((unsigned int)fn_layer) << COMPOSITE_KEY_NUM) + composite_mark;
    }
		bool sameOrigin(bool origin[MAX_ROW][MAX_COL]);
		void copyOrigin(bool origin[MAX_ROW][MAX_COL]);

    std::vector<KeyCode> code_to_send; // 这里的code都是处理好的，需要最终发送的键码
    std::vector<KeyRemainDeloy> key_holding; // 这里做的比较trick，是用于自动降层的
    unsigned char fn_layer;
    unsigned char composite_mark;
		bool origin[MAX_ROW][MAX_COL];
};

#endif //CPPTEST_KEYSTATE_H
