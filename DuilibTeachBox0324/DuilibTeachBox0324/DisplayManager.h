/**
 *@file
 *�ļ����ƣ�DisplayManager.h
 *ժҪ��led�Լ���������ʾ�豸���������
 *@author fly1992@163.com
 **/
#pragma once
#include "GlobalVar.h"
///��ʾ�豸�࣬��Ҫ����led
class CDisplayDev
{
public:
	virtual ~CDisplayDev(){}
	 virtual void On(int iValue);
	 virtual void Off(int iValue);
private:
	static int disPlayDevValue;
};
///��ʾ�豸�����չ����Ҫ����bee
class CDisplayBee:public CDisplayDev
{
public:
	void On(int iValue);
private:
	static const int DELAYMS=1000;
};
///�豸�����࣬��ʼ��led�Լ�bee����
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
