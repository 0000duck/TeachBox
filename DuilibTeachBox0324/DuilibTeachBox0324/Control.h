/**
*@file
*�ļ����ƣ�Control.h
*
*ժҪ�����ڿؼ��ṹ�嶨�巽�����
*
*@author fly1992@163.com
*
**/
#pragma once
///��������ҵ�ļ�����ť
struct FileButtonControl
{
	CButtonUI* m_pButtonMenu1;		
	CButtonUI* m_pButtonMenu2;
	CButtonUI* m_pButtonMenu3;
	CButtonUI* m_pButtonMenu4;
	CButtonUI* m_pButtonMenu5;
	CButtonUI* m_pButtonMenu6;
	CButtonUI* m_pButtonReturn;
};
///�����˸���״̬�ؼ�
struct StateControl
{
	CControlUI* m_pRobotModelIcon;
	CControlUI* m_pRobotDriverIcon;
	CControlUI* m_pRobotSpeedIcon;
	CControlUI* m_pRobotExecuIcon;
	CControlUI* m_pRobotCoordIcon;
	CControlUI* m_pRobotSyncIcon;
	CControlUI* m_pRobotObjIcon;

	CControlUI* m_pRobotModelText;
	CControlUI* m_pRobotDriverText;
	CControlUI* m_pRobotSpeedText;
	CControlUI* m_pRobotExecuText;
	CControlUI* m_pRobotCoordText;
	CControlUI* m_pRobotSyncText;
	CControlUI* m_pRobotObjText;
};
///������������ؼ�
struct CoordControl
{
	CControlUI* m_pRobotAxis1;
	CControlUI* m_pRobotAxis2;	
	CControlUI* m_pRobotAxis3;
	CControlUI* m_pRobotAxis4;	
	CControlUI* m_pRobotAxis5;
	CControlUI* m_pRobotAxis6;
	CControlUI* m_pRobotAxis7;
};