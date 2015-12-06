/**
*@file
*文件名称：CRobot.h
*
*摘要：机器人类，引用其他状态类及命令控制类
*
*@author fly1992@163.com
**/
#pragma  once
#include "CState.h"
#include "CServe.h"
#include "CSpeed.h"
#include "CCoord.h"
#include "CSync.h"
#include "CModel.h"
#include "CRobotObj.h"
#include "CAxisControl.h"
class CRobot
{
public:
	void DisplayState(CRobotState* cstate,CControlUI* controlText,CControlUI* controlImage);
public:
	static CServe* m_pServe;
	static CSpeed* m_pSpeed;
	static CCoord* m_pCoord;
	static CSync*  m_pSync;
	static CModel* m_pModel;
	static CRobotObj* m_pRobotObj;
	static CAxisControl* m_pAxisControl;
	static CInstrControl* m_pInstrControl;
	static CJobControl* m_pJobControl;
};//forget;

