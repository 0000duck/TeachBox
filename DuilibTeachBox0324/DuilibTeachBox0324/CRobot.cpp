/**
*@file
*文件名称：CRobot.cpp
*
*摘要：机器人类，引用其他状态类及命令控制类
*
*@author fly1992@163.com
**/
#include "CRobot.h"

CServe* CRobot::m_pServe=new CServe;
CSpeed* CRobot::m_pSpeed=new CSpeed;
CCoord* CRobot::m_pCoord=new CCoord;
CSync*	CRobot::m_pSync=new CSync;
CModel*	CRobot::m_pModel=new CModel;

CRobotObj*	CRobot::m_pRobotObj=new CRobotObj;
CAxisControl* CRobot::m_pAxisControl=new CAxisControl;
CInstrControl* CRobot::m_pInstrControl=new CInstrControl;
CJobControl* CRobot::m_pJobControl=new CJobControl;
///完成机器人各种状态切换
void CRobot::DisplayState(CRobotState* cstate,CControlUI* controlText,CControlUI* controlImage)
{
	///只有在伺服状态下才能进行相应的操作，间接屏蔽了键盘的响应
	if(cstate==m_pServe||m_pServe->GetState()==CRobotStateValue::SERVEON)
	{
		if (cstate==m_pRobotObj&&m_pSync->GetState()==CRobotStateValue::UNSYNC)
		{
			m_pSync->DisplayTips(CTips::errorInfoProduct,PLEASE_SYNC_MODEL);
			return;
		}
		else
			cstate->DisplayState(controlText,controlImage);
	}
	else if (m_pServe->GetState()==CRobotStateValue::SERVEOFF)
	{
		
		m_pServe->DisplayTips(CTips::errorInfoProduct,SERVE_NOT_OPEN);
	}
}

