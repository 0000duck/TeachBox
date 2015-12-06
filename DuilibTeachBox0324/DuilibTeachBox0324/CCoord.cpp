/**
 *@file
 *文件名称：CCoord.cpp
 *
 *摘要：用于控制机器人坐标切换
 *@author fly1992@163.com
 *
 **/
#include "CCoord.h"
///坐标切换时不同坐标系下的坐标标志
static const wchar_t *pCartCoordFlag[7]={_T("X"),_T("Y"),_T("Z"),_T("A"),_T("B"),_T("C"),_T("")};
static const wchar_t *pJointCoordFlag[7]={_T("S"),_T("L"),_T("U"),_T("R"),_T("B"),_T("T"),_T("")};
static const wchar_t *pToolCoordFlag[7]={_T("TX"),_T("TY"),_T("TZ"),_T("TA"),_T("TB"),_T("TC"),_T("")};
static const wchar_t *pUserCoordFlag[7]={_T("UX"),_T("UY"),_T("UZ"),_T("UA"),_T("UB"),_T("UC"),_T("")};
static const wchar_t *pPosCoordFlag[7]={_T("A1"),_T("A2"),_T(""),_T(""),_T(""),_T(""),_T("")};
/**
 *@brief 构造坐标状态
 *函数名称：CCoord
 *函数功能：构造坐标状态，设置当前坐标状态，构造通信对象
 **/
CCoord::CCoord()
{
	m_pCoordCartState=new CCoordCartState;
	m_pCoordJointState=new CCoordJointState;
	m_pCoordToolState=new CCoordToolState;
	m_pCoordUserState=new CCoordUserState;
	m_pCurrentCoordState=m_pCoordUserState;
	SetState(CRobotStateValue::COORDUSER);///<状态默认值
}
/**
 *@brief 显示坐标状态
 *函数名称：DisplayState
 *函数功能：显示坐标状态
 *@param CControlUI* 坐标状态控件文本和图像资源 
 *@return 
 **/
void CCoord::DisplayState(CControlUI* controlText,CControlUI* controlImage)
{
	if (m_pCurrentCoordState==m_pCoordJointState)
	{
		SetState(CRobotStateValue::COORDCART);
		m_pComm->SendData(InstrDataFactory::pCoordCartData);
		m_pCoordCartState->DisplayState(controlText,controlImage);
		m_pCurrentCoordState=m_pCoordCartState;
		DisplayTips(CTips::tipsInfoProduct,CART_COORD);
		SetRobotCoord(pCartCoordFlag);

	}
	else if(m_pCurrentCoordState==m_pCoordCartState)
	{
		SetState(CRobotStateValue::COORDTOOL);
		m_pComm->SendData(InstrDataFactory::pCoordToolData);
		m_pCoordToolState->DisplayState(controlText,controlImage);
		m_pCurrentCoordState=m_pCoordToolState;
		DisplayTips(CTips::tipsInfoProduct,TOOL_COORD);
		SetRobotCoord(pToolCoordFlag);
	}
	else if(m_pCurrentCoordState==m_pCoordToolState)
	{
		SetState(CRobotStateValue::COORDUSER);
		m_pComm->SendData(InstrDataFactory::pCoordUserData);
		m_pCoordUserState->DisplayState(controlText,controlImage);
		m_pCurrentCoordState=m_pCoordUserState;
		DisplayTips(CTips::tipsInfoProduct,USER_COORD);
		SetRobotCoord(pUserCoordFlag);

	}
	else 
	{
		SetState(CRobotStateValue::COORDJOINT);
		m_pComm->SendData(InstrDataFactory::pCoordJointData);
		m_pCoordJointState->DisplayState(controlText,controlImage);
		m_pCurrentCoordState=m_pCoordJointState;
		DisplayTips(CTips::tipsInfoProduct,JOINT_COORD);
		SetRobotCoord(pJointCoordFlag);
	}

}
/**
*@brief 设置坐标标志
*函数名称：SetRobotCoord
*函数功能：设置坐标标志
*@param const wchar_t ** 坐标标志字符指针的指针 
*@return 
**/
void CCoord::SetRobotCoord(const wchar_t **pAxis)
{
	m_pcoordControl->m_pRobotAxis1->SetText(pAxis[0]);
	m_pcoordControl->m_pRobotAxis2->SetText(pAxis[1]);
	m_pcoordControl->m_pRobotAxis3->SetText(pAxis[2]);
	m_pcoordControl->m_pRobotAxis4->SetText(pAxis[3]);
	m_pcoordControl->m_pRobotAxis5->SetText(pAxis[4]);
	m_pcoordControl->m_pRobotAxis6->SetText(pAxis[5]);
}
/**
*@brief    设置显示坐标标志的控件
*函数名称：SetCoordControl
*函数功能：设置显示坐标标志的控件
*@param CoordControl* 坐标标志的控件指针对应的结构体指针
*@return 
**/
void CCoord::SetCoordControl(CoordControl* coordControl)
{
	m_pcoordControl=coordControl;
}
/**
*@brief    关节坐标系下变位机和机器人本体的轴显示切换
*函数名称：PosAndJointCoordSwitch
*函数功能：关节坐标系下变位机和机器人本体的轴显示切换
*@return 
**/
void CCoord::PosAndJointCoordSwitch()
{
	static bool bflag=1;
	if (bflag){
		SetRobotCoord(pPosCoordFlag);
		bflag=0;
	}
	else {
		SetRobotCoord(pJointCoordFlag);
		bflag=1;
	}
}

