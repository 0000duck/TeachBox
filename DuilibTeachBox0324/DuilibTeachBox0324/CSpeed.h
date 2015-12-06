/**
 *@file
 *�ļ����ƣ�CSpeed.h
 *
 *ժҪ�����ڿ��ƻ�����ʾ���ٶ����ã����е�
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
///�л�ʾ���ٶ���
class CSpeed:public CRobotState
{
public:
	CSpeed();
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
private:
	CState* m_pCurrentSpeedState;
	CState* m_pSpeedLowState;
	CState* m_pSpeedMidState;
	CState* m_pSpeedHighState;
};
