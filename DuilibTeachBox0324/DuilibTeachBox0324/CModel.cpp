/**
 *@file
 *文件名称：CModel.cpp
 *
 *摘要：用于控制机器人模式状态
 *@author fly1992@163.com
 *
 **/
#include "CModel.h"
/**
 *@brief 构造机器人示教模式或者再现模式状态
 *函数名称：CModel
 *函数功能：构造机器人示教模式或者再现模式状态
 **/
CModel::CModel()
{
	m_pModelTeachState=new CModelTeachState;
	m_pModelReplayState=new CModelReplayState;
	m_pCurrentModelState=m_pModelTeachState;
	SetState(CRobotStateValue::MODELTEACH);///<状态默认值
}

/**
 *@brief
 *函数名称：DisplayState
 *函数功能：显示机器人模式状态
 * @param CControlUI* 模式状态控件的图片和文本资源 
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


