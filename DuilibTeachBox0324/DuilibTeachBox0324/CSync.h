/**
 *@file
 *文件名称：CSync.h
 *
 *摘要：用于控制机器人同步状态
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
///同步状态类，切换状态为同步还是非同步
class CSync:public CRobotState
{
public:
	CSync();
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
private:
	CState* m_pSyncState;
	CState* m_pUnsyncState;
	CState* m_pCurrentSyncState;
};