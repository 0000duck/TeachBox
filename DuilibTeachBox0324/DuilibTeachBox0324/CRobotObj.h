/**
 *@file
 *�ļ����ƣ�CRobotObj.h
 *
 *ժҪ�����ڿ��ƻ����˲�������
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
///���ƶ����л���
class CRobotObj:public CRobotState
{
public:
	CRobotObj();
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
private:
	CState* m_pCurrentRobotObj;
	CState* m_pRobotBase;///<�����˱���
	CState* m_pRobotPos;///<�����˼ӱ�λ��
};