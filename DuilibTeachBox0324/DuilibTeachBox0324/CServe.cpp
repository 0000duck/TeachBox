/**
 *@file
 *文件名称：CServe.cpp
 *
 *摘要：用于控制机器人伺服状态开关
 *@author fly1992@163.com
 *
 **/
#include "CServe.h"
/**
 *@brief 构造伺服开关状态，设置当前伺服状态，构造通信对象
 *函数名称：CServe
 *函数功能：构造伺服开关状态，设置当前伺服状态，构造通信对象
 **/
CServe::CServe()
{
	m_pServeOnState=new CServeOnState;
	m_pServeOffState=new CServeOffState;
	m_pCurrentServeState=m_pServeOffState;
	SetState(CRobotStateValue::SERVEOFF);///<状态默认值
}

/**
 *@brief 显示伺服状态
 *函数名称：DisplayServeState
 *函数功能：显示伺服状态
 * @param CControlUI* 伺服状态控件的文本和图片资源 
 * @return 
 **/
void CServe::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	if (m_pCurrentServeState==m_pServeOffState)
	{
		SetState(CRobotStateValue::SERVEON);
		m_pComm->SendData(InstrDataFactory::pServeOnData);
		m_pServeOnState->DisplayState(controlText,controlImage);
		m_pCurrentServeState=m_pServeOnState;
		DisplayTips(CTips::tipsInfoProduct,SERVE_OPENED);
		CDisplayDevManager::displayLed->On(CDisplayDevManager::LEDMOTION);

	}
	else
	{
		SetState(CRobotStateValue::SERVEOFF);
		m_pComm->SendData(InstrDataFactory::pServeOffData);
		m_pServeOffState->DisplayState(controlText,controlImage);
		m_pCurrentServeState=m_pServeOffState;
		DisplayTips(CTips::tipsInfoProduct,PLEASE_OPEN_SERVE);
		CDisplayDevManager::displayLed->Off(CDisplayDevManager::LEDMOTION);
	}
}


