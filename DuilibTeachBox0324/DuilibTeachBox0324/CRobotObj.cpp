/**
 *@file
 *�ļ����ƣ�CRobotObj.cpp
 *
 *ժҪ�������л����ƶ���
 *@author fly1992@163.com
 *
 **/
#include "CRobotObj.h"
/**
 *@brief ������ƶ���״̬�����õ�ǰ���ƶ���״̬
 *�������ƣ�CRobotObj
 *�������ܣ�������ƶ���״̬�����õ�ǰ���ƶ���״̬
 **/
CRobotObj::CRobotObj()
{
	m_pRobotBase=new CRobotBaseState;
	m_pRobotPos=new CRobotPosState;///<�����˼ӱ�λ��
	m_pCurrentRobotObj=m_pRobotBase;
	SetState(CRobotStateValue::ROBOTBASE);///<״̬Ĭ��ֵ
}

/**
 *@brief �л����ƶ���
 *�������ƣ�DisplayState
 *�������ܣ���ʾ�ŷ�״̬
 * @param CControlUI* ����״̬�ؼ���ͼƬ���ı���Դ
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


