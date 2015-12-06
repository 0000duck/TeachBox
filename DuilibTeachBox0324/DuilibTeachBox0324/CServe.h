/**
 *@file
 *�ļ����ƣ�CServe.h
 *
 *ժҪ�����ڿ��ƻ������ŷ�״̬����
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
///�ŷ�״̬�л���
class CServe:public CRobotState
{
public:
	CServe();
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
private:
	CState* m_pCurrentServeState;
	CState* m_pServeOnState;
	CState* m_pServeOffState;
};