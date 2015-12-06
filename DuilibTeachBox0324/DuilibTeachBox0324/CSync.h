/**
 *@file
 *�ļ����ƣ�CSync.h
 *
 *ժҪ�����ڿ��ƻ�����ͬ��״̬
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
///ͬ��״̬�࣬�л�״̬Ϊͬ�����Ƿ�ͬ��
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