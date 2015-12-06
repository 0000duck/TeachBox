/**
 *@file
 *文件名称：DisplayManager.h
 *摘要：led以及蜂鸣器显示设备的输出声明
 *@author fly1992@163.com
 **/
#pragma once
#include "GlobalVar.h"
///显示设备类，主要用于led
class CDisplayDev
{
public:
	virtual ~CDisplayDev(){}
	 virtual void On(int iValue);
	 virtual void Off(int iValue);
private:
	static int disPlayDevValue;
};
///显示设备类的扩展，主要用于bee
class CDisplayBee:public CDisplayDev
{
public:
	void On(int iValue);
private:
	static const int DELAYMS=1000;
};
///设备管理类，初始化led以及bee对象
class CDisplayDevManager
{
public:
	enum{
		LEDRUN=TEACHBOX_LED1,
		LEDERROR=TEACHBOX_LED2,
		LEDMOTION=TEACHBOX_LED3,
		LEDPROCESS=TEACHBOX_LED4,
		BUZZER=TEACHBOX_BUZZER
		};
	static CDisplayDev* displayLed;
	static CDisplayDev* displayBee;
};
