/**
 *@file
 *文件名称：CServe.h
 *
 *摘要：用于控制机器人伺服状态开关
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
///伺服状态切换类
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