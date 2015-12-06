/**
*@file
*文件名称：Control.h
*
*摘要：窗口控件结构体定义方便管理
*
*@author fly1992@163.com
*
**/
#pragma once
///机器人作业文件处理按钮
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
///机器人各种状态控件
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
///机器人坐标轴控件
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