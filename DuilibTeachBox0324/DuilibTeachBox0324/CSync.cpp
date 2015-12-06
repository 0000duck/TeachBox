/**
 *@file
 *文件名称：CSync.cpp
 *
 *摘要：用于控制机器人同步状态
 *@author fly1992@163.com
 *
 **/
#include "CSync.h"
/**
 *@file
 *函数名称：CSync
 *函数功能：构造机器人同步状态
 **/
CSync::CSync()
{
	m_pSyncState=new CSyncState;
	m_pUnsyncState=new CUnsyncState;
	m_pCurrentSyncState=m_pUnsyncState;
	SetState(CRobotStateValue::UNSYNC);///<状态默认值
}

/**
 *@file
 *函数名称：DisplayServeState
 *函数功能：显示机器人同步状态
 * @param CControlUI* 同步状态控件的指针 
 * @return 
 **/
void CSync::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	if (m_pCurrentSyncState==m_pUnsyncState)
	{
		SetState(CRobotStateValue::SYNC);
		m_pComm->SendData(InstrDataFactory::pSyncData);
		m_pSyncState->DisplayState(controlText,controlImage);
		m_pCurrentSyncState=m_pSyncState;
		DisplayTips(CTips::tipsInfoProduct,SYNC_MODEL);
	}
	else
	{
		SetState(CRobotStateValue::UNSYNC);
		m_pComm->SendData(InstrDataFactory::pUnsyncData);
		m_pUnsyncState->DisplayState(controlText,controlImage);
		m_pCurrentSyncState=m_pUnsyncState;
		DisplayTips(CTips::tipsInfoProduct,UNSYNC_MODEL);
	}
}


