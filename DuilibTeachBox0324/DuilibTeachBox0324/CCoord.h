/**
 *@file
 *�ļ����ƣ�CCoord.h
 *
 *ժҪ�����ڿ��ƻ������������ã��ؽڣ�ֱ�ǣ����ߣ��û�������л�
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
#include "Control.h"
///����������״̬�л��࣬��������л�����
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
