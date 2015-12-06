/**
 *@file
 *�ļ����ƣ�CServe.cpp
 *
 *ժҪ�����ڿ��ƻ������ŷ�״̬����
 *@author fly1992@163.com
 *
 **/
#include "CServe.h"
/**
 *@brief �����ŷ�����״̬�����õ�ǰ�ŷ�״̬������ͨ�Ŷ���
 *�������ƣ�CServe
 *�������ܣ������ŷ�����״̬�����õ�ǰ�ŷ�״̬������ͨ�Ŷ���
 **/
CServe::CServe()
{
	m_pServeOnState=new CServeOnState;
	m_pServeOffState=new CServeOffState;
	m_pCurrentServeState=m_pServeOffState;
	SetState(CRobotStateValue::SERVEOFF);///<״̬Ĭ��ֵ
}

/**
 *@brief ��ʾ�ŷ�״̬
 *�������ƣ�DisplayServeState
 *�������ܣ���ʾ�ŷ�״̬
 * @param CControlUI* �ŷ�״̬�ؼ����ı���ͼƬ��Դ 
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


