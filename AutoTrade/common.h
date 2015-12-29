#pragma once

#include "stdafx.h"

//��������
//0,1,2,3 �򿪣���������ƽ����ƽ
const int BUYOPEN = 0;
const int SELLOPEN = BUYOPEN + 1;
const int BUYCLOSE = SELLOPEN + 1;
const int SELLCLOSE = BUYCLOSE + 1;
const int STEPCOUNT = SELLCLOSE + 1;

//operation
const int KEY = 1000;
const int INPUTEDIT = KEY + 1;
const int CLICK = INPUTEDIT + 1;
const int SLEEP = CLICK + 1;

//type of input
const int NONE = 2000;
const int ZQBH = NONE + 1;
const int JG = ZQBH + 1;
const int SL = JG + 1;

struct ScreenPos {
	unsigned short x;
	unsigned short y;
};

struct Step {
	int index;
	std::string windowName;
	int op;
	union {
		int keyValue;
		int typeValue; //when op = INPUT
		ScreenPos clickPosValue;
		int sleepValue;
	} value;
};
