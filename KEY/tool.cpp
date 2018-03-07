//
// Created by liu on 2017/11/28.
//

#ifdef __cplusplus
extern "C" {
#endif 
#include "hw_config.h"
#ifdef __cplusplus
}
#endif 

#include "tool.h"
#include "delay.h"
#include "vector"

char isSameCom(const std::vector<KeyCode> &keys_to_sent) {
	char num = keys_to_sent.size();
	if (num <= 1) return 1;
	char co = keys_to_sent[0].getComposite();
	for (int i = 1; i < num; ++i) {
		if (co != keys_to_sent[0].getComposite()) return 0;
	}
	return 1;
}

void tool::sent_key_code(const std::vector<KeyCode> &keys_to_sent) {
	char num = keys_to_sent.size();
	if (num == 0) {
		Joystick_Send(0, 0, 0, 0, 0, 0, 0, 0);
	} else if (num == 1) {
		char c = keys_to_sent[0].getComposite();
		char co = keys_to_sent[0].getCode();
		Joystick_Send(c, 0, co, 0, 0, 0, 0, 0);
	} else if (isSameCom(keys_to_sent)) { // 同一minilayer的可以 6 并行传送
		char c = keys_to_sent[0].getComposite();
		char co[6];
		for (int i = 0; i < 6; ++i) {
			co[i] = (i < num)? keys_to_sent[i].getCode(): 0;
		}
		Joystick_Send(c, 0, co[0], co[1], co[2], co[3], co[4], co[5]);
	} else {
		for (int i = 0; i < num; ++i) {
			char c = keys_to_sent[i].getComposite();
			char co = keys_to_sent[i].getCode();
			Joystick_Send(c, 0, co, 0, 0, 0, 0, 0);
		}
	}
}
