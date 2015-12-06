/**
 *@file
 *文件名称：CSpeed.h
 *
 *摘要：用于控制机器人示教速度设置，高中低
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
///切换示教速度类
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
