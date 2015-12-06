/**
 *@file
 *�ļ����ƣ�CCoord.cpp
 *
 *ժҪ�����ڿ��ƻ����������л�
 *@author fly1992@163.com
 *
 **/
#include "CCoord.h"
///�����л�ʱ��ͬ����ϵ�µ������־
static const wchar_t *pCartCoordFlag[7]={_T("X"),_T("Y"),_T("Z"),_T("A"),_T("B"),_T("C"),_T("")};
static const wchar_t *pJointCoordFlag[7]={_T("S"),_T("L"),_T("U"),_T("R"),_T("B"),_T("T"),_T("")};
static const wchar_t *pToolCoordFlag[7]={_T("TX"),_T("TY"),_T("TZ"),_T("TA"),_T("TB"),_T("TC"),_T("")};
static const wchar_t *pUserCoordFlag[7]={_T("UX"),_T("UY"),_T("UZ"),_T("UA"),_T("UB"),_T("UC"),_T("")};
static const wchar_t *pPosCoordFlag[7]={_T("A1"),_T("A2"),_T(""),_T(""),_T(""),_T(""),_T("")};
/**
 *@brief ��������״̬
 *�������ƣ�CCoord
 *�������ܣ���������״̬�����õ�ǰ����״̬������ͨ�Ŷ���
 **/
CCoord::CCoord()
{
	m_pCoordCartState=new CCoordCartState;
	m_pCoordJointState=new CCoordJointState;
	m_pCoordToolState=new CCoordToolState;
	m_pCoordUserState=new CCoordUserState;
	m_pCurrentCoordState=m_pCoordUserState;
	SetState(CRobotStateValue::COORDUSER);///<״̬Ĭ��ֵ
}
/**
 *@brief ��ʾ����״̬
 *�������ƣ�DisplayState
 *�������ܣ���ʾ����״̬
 *@param CControlUI* ����״̬�ؼ��ı���ͼ����Դ 
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
*@brief ���������־
*�������ƣ�SetRobotCoord
*�������ܣ����������־
*@param const wchar_t ** �����־�ַ�ָ���ָ�� 
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
*@brief    ������ʾ�����־�Ŀؼ�
*�������ƣ�SetCoordControl
*�������ܣ�������ʾ�����־�Ŀؼ�
*@param CoordControl* �����־�Ŀؼ�ָ���Ӧ�Ľṹ��ָ��
*@return 
**/
void CCoord::SetCoordControl(CoordControl* coordControl)
{
	m_pcoordControl=coordControl;
}
/**
*@brief    �ؽ�����ϵ�±�λ���ͻ����˱��������ʾ�л�
*�������ƣ�PosAndJointCoordSwitch
*�������ܣ��ؽ�����ϵ�±�λ���ͻ����˱��������ʾ�л�
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

