#pragma once

#include "stdafx.h"
#include "common.h"

class AutoTrade
{
public:
	AutoTrade(void);
	~AutoTrade(void);
	void buy();
	void sell();
	void runStep(const char *code, int type, float price, int vol);
	void printStep();


private:
	void initVkmap();
	void initConfig();
	int selectWindow(std::string windowName);
	int forgroundWindow(std::string windowName);
	void mouseMove(int x, int y);
	void mouseClick(int button, int times);
	void keyPress(int vk);
	void keyPressString(const char *str);

	void testWindow();

	std::string configName;
	std::vector<Step> stepv[STEPCOUNT]; //0,1,2,3 �򿪣���������ƽ����ƽ
	std::map<std::string, UINT8> vkmap;
};

