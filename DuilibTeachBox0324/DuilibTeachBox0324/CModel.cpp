/**
 *@file
 *�ļ����ƣ�CModel.cpp
 *
 *ժҪ�����ڿ��ƻ�����ģʽ״̬
 *@author fly1992@163.com
 *
 **/
#include "CModel.h"
/**
 *@brief ���������ʾ��ģʽ��������ģʽ״̬
 *�������ƣ�CModel
 *�������ܣ����������ʾ��ģʽ��������ģʽ״̬
 **/
CModel::CModel()
{
	m_pModelTeachState=new CModelTeachState;
	m_pModelReplayState=new CModelReplayState;
	m_pCurrentModelState=m_pModelTeachState;
	SetState(CRobotStateValue::MODELTEACH);///<״̬Ĭ��ֵ
}

/**
 *@brief
 *�������ƣ�DisplayState
 *�������ܣ���ʾ������ģʽ״̬
 * @param CControlUI* ģʽ״̬�ؼ���ͼƬ���ı���Դ 
 * @return 
 **/
void CModel::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	if (m_pCurrentModelState==m_pModelTeachState)
	{
		SetState(CRobotStateValue::MODELREPALY);
		m_pComm->SendData(InstrDataFactory::pModelReplayData);
		m_pModelReplayState->DisplayState(controlText,controlImage);
		m_pCurrentModelState=m_pModelReplayState;
		DisplayTips(CTips::tipsInfoProduct,MODEL_REPALY);
	}
	else
	{
		SetState(CRobotStateValue::MODELTEACH);
		m_pComm->SendData(InstrDataFactory::pModelTeachData);
		m_pModelTeachState->DisplayState(controlText,controlImage);
		m_pCurrentModelState=m_pModelTeachState;
		DisplayTips(CTips::tipsInfoProduct,MODEL_TEACH);
	}
}


