/**
 *@file
 *�ļ����ƣ�CModel.h
 *
 *ժҪ�����ڿ��ƻ�����ʾ��ģʽ����
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
///������ģʽ�л���
class CModel:public CRobotState
{
public:
	CModel();
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
private:
	CState* m_pCurrentModelState;
	CState* m_pModelTeachState;
	CState* m_pModelReplayState;
};