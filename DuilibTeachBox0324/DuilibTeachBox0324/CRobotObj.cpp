/**
 *@file
 *文件名称：CRobotObj.cpp
 *
 *摘要：用于切换控制对象
 *@author fly1992@163.com
 *
 **/
#include "CRobotObj.h"
/**
 *@brief 构造控制对象状态，设置当前控制对象状态
 *函数名称：CRobotObj
 *函数功能：构造控制对象状态，设置当前控制对象状态
 **/
CRobotObj::CRobotObj()
{
	m_pRobotBase=new CRobotBaseState;
	m_pRobotPos=new CRobotPosState;///<机器人加变位机
	m_pCurrentRobotObj=m_pRobotBase;
	SetState(CRobotStateValue::ROBOTBASE);///<状态默认值
}

/**
 *@brief 切换控制对象
 *函数名称：DisplayState
 *函数功能：显示伺服状态
 * @param CControlUI* 对象状态控件的图片和文本资源
 * @return 
 **/
void CRobotObj::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	if (m_pCurrentRobotObj==m_pRobotBase)
	{
		SetState(CRobotStateValue::POSTIONER);
		m_pComm->SendData(InstrDataFactory::pRobotPosData);
		m_pRobotPos->DisplayState(controlText,controlImage);
		m_pCurrentRobotObj=m_pRobotPos;
		DisplayTips(CTips::tipsInfoProduct,ROBOT_POSITIONER);
	}
	else
	{
		SetState(CRobotStateValue::ROBOTBASE);
		m_pComm->SendData(InstrDataFactory::pRobotBaseData);
		m_pRobotBase->DisplayState(controlText,controlImage);
		m_pCurrentRobotObj=m_pRobotBase;
		DisplayTips(CTips::tipsInfoProduct,ROBOT_BASE);
	}
}


