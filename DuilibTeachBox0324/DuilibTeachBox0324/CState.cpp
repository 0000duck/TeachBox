/**
*@file
*文件名称：CState.cpp
*
*摘要：状态基类，可用于派生出其他状态类，完成状态切换
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
 *@brief 设置状态标志
 *函数名称：SetState
 *函数功能：设置状态标志
 **/
void CRobotState::SetState(int iFlag)
{
	m_iFlag=iFlag;
}
/**
*@brief 根据信息类型，显示错误信息，并激活蜂鸣器提示
*函数名称：DisplayTips
*函数功能：根据信息类型，显示错误信息，并激活蜂鸣器提示
*@param CTipsElementProduct& 错误信息显示项
*@param ERRORMSGINDEX 信息索引
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
///获取当前状态标志
int CRobotState::GetState()
{
	return m_iFlag;
}
///设置控件的图片和文本
void CState::SetTextAndBkImg(CControlUI* controlText,CStdString strText,CControlUI* controlImage,CStdString strBkimg)
{
	controlText->SetText(strText);
	controlImage->SetBkImage(strBkimg);
}
///伺服状态显示，开关两种状态
void CServeOnState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("伺服开"),controlImage,_T("motor.png"));
}

void CServeOffState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("伺服关"),controlImage,_T("motoroff.png"));
}
///示教速度状态显示，分别为低中高三种状态
void CSpeedLowState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("低速"),controlImage,_T("LowSpeed.png"));
}

void CSpeedMidState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("中速"),controlImage,_T("MidSpeed.png"));
}

void CSpeedHighState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("高速"),controlImage,_T("HighSpeed.png"));
}
///坐标状态显示，分别为直角、关节、用户、工具状态
void CCoordCartState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("直角"),controlImage,_T("CartCoord.png"));
}
void CCoordJointState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("关节"),controlImage,_T("JointCoord.png"));
}
void CCoordToolState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("工具"),controlImage,_T("ToolCoord.png"));
}
void CCoordUserState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("用户"),controlImage,_T("UserCoord.png"));
}
///机器人同步状态
void CSyncState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("同步"),controlImage,_T("SynchronizedRobot.png"));
}
void CUnsyncState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("非同步"),controlImage,_T("SingleRobot.png"));
}
///机器人对象同步状态
void CRobotBaseState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("机器人1"),controlImage,_T("Robot1.png"));
}
void CRobotPosState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("变位机"),controlImage,_T("BianWeiJi.png"));
}

///机器人模式状态
void CModelTeachState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("示教模式"),controlImage,_T("TeachModel.png"));
}
void CModelReplayState::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	SetTextAndBkImg(controlText,_T("再现模式"),controlImage,_T("CircleModel.png"));
}




