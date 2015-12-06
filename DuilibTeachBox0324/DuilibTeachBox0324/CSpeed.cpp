/**
 *@file
 *�ļ����ƣ�CSpeed.cpp
 *
 *ժҪ�����ڿ��ƻ�����ʾ���ٶȴ�С
 *@author fly1992@163.com
 *
 **/
#include "CSpeed.h"
/**
 *@brief �����ٶȴ�С״̬�����õ�ǰ�ŷ�״̬
 *�������ƣ�CSpeed
 *�������ܣ������ٶȴ�С״̬�����õ�ǰ�ŷ�״̬
 **/
CSpeed::CSpeed()
{
	m_pSpeedLowState=new CSpeedLowState;
	m_pSpeedMidState=new CSpeedMidState;
	m_pSpeedHighState=new CSpeedHighState;
	m_pCurrentSpeedState=m_pSpeedLowState;
	SetState(CRobotStateValue::SPEEDLOW);///<״̬Ĭ��ֵ
}

/**
 *@brief ��ʾ�ٶ�״̬
 *�������ƣ�DisplayState
 *�������ܣ���ʾ�ŷ�״̬
 * @param CControlUI* �ٶ�״̬�ؼ����ı���ͼƬ��Դ
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


