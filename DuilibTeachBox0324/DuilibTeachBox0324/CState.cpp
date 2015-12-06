/**
*@file
*�ļ����ƣ�CState.cpp
*
*ժҪ��״̬���࣬����������������״̬�࣬���״̬�л�
*
*@author fly1992@163.com
*
**/
#include "CState.h"
CRobotState::CRobotState()
{
	m_pComm=new CCommunication;
}
/**
 *@brief ����״̬��־
 *�������ƣ�SetState
 *�������ܣ�����״̬��־
 **/
void CRobotState::SetState(int iFlag)
{
	m_iFlag=iFlag;
}
/**
*@brief ������Ϣ���ͣ���ʾ������Ϣ���������������ʾ
*�������ƣ�DisplayTips
*�������ܣ�������Ϣ���ͣ���ʾ������Ϣ���������������ʾ
*@param CTipsElementProduct& ������Ϣ��ʾ��
*@param ERRORMSGINDEX ��Ϣ����
**/
void CDisplayTips::DisplayTips(CTipsElementProduct &tipsProduct,ERRORMSGINDEX errorIndex)
{

	CTips::GetInstance(NULL)->AddTips(tipsProduct,errorIndex);
	CTips::GetInstance(NULL)->CurrentTipsDisplay();
	if(CTips::GetInstance(NULL)->GetErrorType()==ERRORINFO)
	{
		CDisplayDevManager::displayLed->On(CDisplayDevManager::LEDERROR);
		CDisplayDevManager::displayBee->On(CDisplayDevManager::BUZZER);
	}	
	else{
		CDisplayDevManager::displayLed->Off(CDisplayDevManager::LEDERROR);
	}
}
///��ȡ��ǰ״̬��־
int CRobotState::GetState()
{
	return m_iFlag;
}
///���ÿؼ���ͼƬ���ı�
void CState::SetTextAndBkImg(CControlUI* controlText,CStdString strText,CControlUI* controlImage,CStdString strBkimg)
{
	controlText->SetText(strText);
	controlImage->SetBkImage(strBkimg);
}
///�ŷ�״̬��ʾ����������״̬
void CServeOnState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("�ŷ���"),controlImage,_T("motor.png"));
}

void CServeOffState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("�ŷ���"),controlImage,_T("motoroff.png"));
}
///ʾ���ٶ�״̬��ʾ���ֱ�Ϊ���и�����״̬
void CSpeedLowState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("����"),controlImage,_T("LowSpeed.png"));
}

void CSpeedMidState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("����"),controlImage,_T("MidSpeed.png"));
}

void CSpeedHighState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("����"),controlImage,_T("HighSpeed.png"));
}
///����״̬��ʾ���ֱ�Ϊֱ�ǡ��ؽڡ��û�������״̬
void CCoordCartState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("ֱ��"),controlImage,_T("CartCoord.png"));
}
void CCoordJointState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("�ؽ�"),controlImage,_T("JointCoord.png"));
}
void CCoordToolState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("����"),controlImage,_T("ToolCoord.png"));
}
void CCoordUserState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("�û�"),controlImage,_T("UserCoord.png"));
}
///������ͬ��״̬
void CSyncState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("ͬ��"),controlImage,_T("SynchronizedRobot.png"));
}
void CUnsyncState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("��ͬ��"),controlImage,_T("SingleRobot.png"));
}
///�����˶���ͬ��״̬
void CRobotBaseState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("������1"),controlImage,_T("Robot1.png"));
}
void CRobotPosState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("��λ��"),controlImage,_T("BianWeiJi.png"));
}

///������ģʽ״̬
void CModelTeachState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("ʾ��ģʽ"),controlImage,_T("TeachModel.png"));
}
void CModelReplayState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("����ģʽ"),controlImage,_T("CircleModel.png"));
}




