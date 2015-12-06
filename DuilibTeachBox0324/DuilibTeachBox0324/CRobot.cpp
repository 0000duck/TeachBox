/**
*@file
*�ļ����ƣ�CRobot.cpp
*
*ժҪ���������࣬��������״̬�༰���������
*
*@author fly1992@163.com
**/
#include "CRobot.h"

CServe* CRobot::m_pServe=new CServe;
CSpeed* CRobot::m_pSpeed=new CSpeed;
CCoord* CRobot::m_pCoord=new CCoord;
CSync*	CRobot::m_pSync=new CSync;
CModel*	CRobot::m_pModel=new CModel;

CRobotObj*	CRobot::m_pRobotObj=new CRobotObj;
CAxisControl* CRobot::m_pAxisControl=new CAxisControl;
CInstrControl* CRobot::m_pInstrControl=new CInstrControl;
CJobControl* CRobot::m_pJobControl=new CJobControl;
///��ɻ����˸���״̬�л�
void CRobot::DisplayState(CRobotState* cstate,CControlUI* controlText,CControlUI* controlImage)
{
	///ֻ�����ŷ�״̬�²��ܽ�����Ӧ�Ĳ�������������˼��̵���Ӧ
	if(cstate==m_pServe||m_pServe->GetState()==CRobotStateValue::SERVEON)
	{
		if (cstate==m_pRobotObj&&m_pSync->GetState()==CRobotStateValue::UNSYNC)
		{
			m_pSync->DisplayTips(CTips::errorInfoProduct,PLEASE_SYNC_MODEL);
			return;
		}
		else
			cstate->DisplayState(controlText,controlImage);
	}
	else if (m_pServe->GetState()==CRobotStateValue::SERVEOFF)
	{
		
		m_pServe->DisplayTips(CTips::errorInfoProduct,SERVE_NOT_OPEN);
	}
}

