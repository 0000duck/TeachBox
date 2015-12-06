/**
 *@file
 *文件名称：CSpeed.cpp
 *
 *摘要：用于控制机器人示教速度大小
 *@author fly1992@163.com
 *
 **/
#include "CSpeed.h"
/**
 *@brief 构造速度大小状态，设置当前伺服状态
 *函数名称：CSpeed
 *函数功能：构造速度大小状态，设置当前伺服状态
 **/
CSpeed::CSpeed()
{
	m_pSpeedLowState=new CSpeedLowState;
	m_pSpeedMidState=new CSpeedMidState;
	m_pSpeedHighState=new CSpeedHighState;
	m_pCurrentSpeedState=m_pSpeedLowState;
	SetState(CRobotStateValue::SPEEDLOW);///<状态默认值
}

/**
 *@brief 显示速度状态
 *函数名称：DisplayState
 *函数功能：显示伺服状态
 * @param CControlUI* 速度状态控件的文本和图片资源
 * @return 
 **/
void CSpeed::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	if (m_pCurrentSpeedState==m_pSpeedLowState)
	{
		SetState(CRobotStateValue::SPEEDMID);
		m_pComm->SendData(InstrDataFactory::pSpeedMidData);
		m_pSpeedMidState->DisplayState(controlText,controlImage);
		m_pCurrentSpeedState=m_pSpeedMidState;
		DisplayTips(CTips::tipsInfoProduct,MID_SPEED);
	}
	else if(m_pCurrentSpeedState==m_pSpeedMidState)
	{
		SetState(CRobotStateValue::SPEEDHIGH);
		m_pComm->SendData(InstrDataFactory::pSpeedHighData);
		m_pSpeedHighState->DisplayState(controlText,controlImage);
		m_pCurrentSpeedState=m_pSpeedHighState;
		DisplayTips(CTips::tipsInfoProduct,HIGH_SPEED);
	}
	else
	{
		SetState(CRobotStateValue::SPEEDLOW);
		m_pComm->SendData(InstrDataFactory::pSpeedLowData);
		m_pSpeedLowState->DisplayState(controlText,controlImage);
		m_pCurrentSpeedState=m_pSpeedLowState;
		DisplayTips(CTips::tipsInfoProduct,LOW_SPEED);
	}
}


