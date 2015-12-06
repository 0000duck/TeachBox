/**
 *@file
 *�ļ����ƣ�CSync.cpp
 *
 *ժҪ�����ڿ��ƻ�����ͬ��״̬
 *@author fly1992@163.com
 *
 **/
#include "CSync.h"
/**
 *@file
 *�������ƣ�CSync
 *�������ܣ����������ͬ��״̬
 **/
CSync::CSync()
{
	m_pSyncState=new CSyncState;
	m_pUnsyncState=new CUnsyncState;
	m_pCurrentSyncState=m_pUnsyncState;
	SetState(CRobotStateValue::UNSYNC);///<״̬Ĭ��ֵ
}

/**
 *@file
 *�������ƣ�DisplayServeState
 *�������ܣ���ʾ������ͬ��״̬
 * @param CControlUI* ͬ��״̬�ؼ���ָ�� 
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


