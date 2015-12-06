/**
 *@file
 *文件名称：CRobotObj.h
 *
 *摘要：用于控制机器人操作对象
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
///控制对象切换类
class CRobotObj:public CRobotState
{
public:
	CRobotObj();
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
private:
	CState* m_pCurrentRobotObj;
	CState* m_pRobotBase;///<机器人本体
	CState* m_pRobotPos;///<机器人加变位机
};