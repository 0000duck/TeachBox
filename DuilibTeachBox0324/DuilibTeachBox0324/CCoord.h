/**
 *@file
 *文件名称：CCoord.h
 *
 *摘要：用于控制机器人坐标设置，关节，直角，工具，用户坐标的切换
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
#include "Control.h"
///机器人坐标状态切换类，完成坐标切换功能
class CCoord:public CRobotState
{
public:
	CCoord();
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
	void SetRobotCoord(const wchar_t **pAxis);
	void SetCoordControl(CoordControl* coordControl);
	void PosAndJointCoordSwitch();
	const wchar_t **pAxis;
private:
	CState* m_pCurrentCoordState;
	CState* m_pCoordCartState;
	CState* m_pCoordJointState;
	CState* m_pCoordToolState;
	CState* m_pCoordUserState;
	CoordControl* m_pcoordControl;
};
