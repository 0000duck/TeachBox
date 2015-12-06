/**
 *@file
 *文件名称：CModel.h
 *
 *摘要：用于控制机器人示教模式设置
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CState.h"
#include "CRobotDataTypeFactory.h"
///机器人模式切换类
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