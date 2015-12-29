#include "stdafx.h"
#include "autoTrade.h"
#include "common.h"

using namespace std;

AutoTrade::AutoTrade(void) {
	initVkmap();
	configName = "config.ini";
	initConfig();

	printStep();
	mouseMove(1800, 500);
	mouseClick(0, 2);
}


AutoTrade::~AutoTrade(void) {

}

void AutoTrade::runStep(int proc) {
	vector<Step> st = stepv[proc];
	for (unsigned int i = 0; i < st.size(); i ++) {

	}
}

void AutoTrade::printStep() {
	for (unsigned int i = 0; i < STEPCOUNT; i ++) {
		cout << "--------------" << i << "----------------" << endl;
		for (unsigned int j = 0; j < stepv[i].size(); j ++) {
			cout << stepv[i][j].windowName << ' ' << stepv[i][j].op << ' ';
			if (stepv[i][j].op == KEY) cout << stepv[i][j].value.keyValue << endl;
			else if (stepv[i][j].op == INPUTEDIT) cout << stepv[i][j].value.typeValue << endl;
			else if (stepv[i][j].op == SLEEP) cout << stepv[i][j].value.sleepValue << endl;
			else if (stepv[i][j].op == CLICK) cout << stepv[i][j].value.clickPosValue.x << ' ' 
												<< stepv[i][j].value.clickPosValue.y << endl;
		}
	}
}

//private
void AutoTrade::initVkmap() {
	vkmap["ESC"] = VK_ESCAPE;
	vkmap["ENTER"] = VK_RETURN;
	vkmap["TAB"] = VK_TAB;
	vkmap["SHIFT"] = VK_SHIFT;
	vkmap["CTRL"] = VK_CONTROL;
	vkmap["ALT"] = VK_MENU;
	vkmap["LEFT"] = VK_LEFT;
	vkmap["RIGHT"] = VK_RIGHT;
	vkmap["UP"] = VK_UP;
	vkmap["DOWN"] = VK_DOWN;
	vkmap["F10"] = VK_F10;
}

void AutoTrade::initConfig() {
	ifstream fin(configName);
	if (!fin) {
		cout << "file open error\n";
		exit(1);
	}

	string line;
	int a = 0;
	int index = 0, n = 0;
	stringstream ss;
	while (getline(fin, line)) {
		if (line.substr(0, 2) == "//") continue;
		if (line.substr(0, 2) == "--") {
			if (line.substr(2, 4) == "买开") {
				index = BUYOPEN;
				cout << line.substr(2, 4) << endl;
				continue;
			} else if (line.substr(2, 4) == "卖开") {
				index = SELLOPEN;
				continue;
			} else if (line.substr(2, 4) == "买平") {
				index = BUYCLOSE;
				continue;
			} else if (line.substr(2, 4) == "卖平") {
				index = SELLCLOSE;
				continue;
			}

		}
		if (line.substr(0, 4) == "步骤") {
			string s1;
			ss >> s1 >> n;
			continue;
		}
		ss.clear();
		ss.str(line);
		string s;
		Step tstep;
		ss >> tstep.windowName >> s;
		if (s == "key") {
			tstep.op = KEY;
			string s1;
			ss >> s1;
			tstep.value.keyValue = vkmap[s1];
		}
		else if (s == "input") {
			tstep.op = INPUTEDIT;
			string s1;
			ss >> s1;
			if (s1 == "ZQBH") tstep.value.typeValue = ZQBH;
			else if (s1 == "JG") tstep.value.typeValue = JG;
			else if (s1 == "SL") tstep.value.typeValue = SL;
			else tstep.value.typeValue = NONE;
		}
		else if (s == "click") {
			tstep.op = CLICK;
			ss >> tstep.value.clickPosValue.x >> tstep.value.clickPosValue.y;
		}
		else if (s == "sleep") {
			tstep.op = SLEEP;
			ss >> tstep.value.sleepValue;
		}
		stepv[index].push_back(tstep);
	}

}

void AutoTrade::mouseMove(int x, int y) {
	double w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CXSCREEN);
	double fx = x*(65536.0/w), fy = y*(65536.0/h);
	INPUT input = {0};
	input.type = INPUT_MOUSE;
	input.mi.dx = (long)fx;
	input.mi.dy = (long)fy;
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(INPUT));
}

void AutoTrade::mouseClick(int button, int times) {
	INPUT input = {0};
	for (int i = 0; i < times; i ++) {
		// left down
		ZeroMemory(&input,sizeof(INPUT));
		input.type = INPUT_MOUSE;
		if (button == 0)
			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		else
			input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1,&input,sizeof(INPUT));
		// left up
		ZeroMemory(&input,sizeof(INPUT));
		input.type = INPUT_MOUSE;
		if (button == 0)
			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		else
			input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1,&input,sizeof(INPUT));
	}
}

void AutoTrade::keyPress(int vk) {
	keybd_event(vk,0,0,0);
	Sleep(100);
	keybd_event(vk,0,KEYEVENTF_KEYUP,0);
	Sleep(100);
}

void AutoTrade::keyPressString(const char *str) {
	const char *c = str;
	while (*c != '\0') {
		if (*c == '.')
			keyPress(VK_DECIMAL);
		else if (*c >= 'A' && *c <= 'Z')
			keyPress(*c);
		else if (*c >= 'a' && *c <= 'z')
			keyPress(*c);
		else if (*c >= '0' && *c <= '9')
			keyPress(*c);
		c ++;
	}	
}


