/**
*@file
*文件名称：CState.h
*
*摘要：状态基类，可用于派生出其他状态类，完成状态切换
*
*@author fly1992@163.com
*
**/
#pragma once
#include "GlobalVar.h"
#include "CCommunication.h"
#include "CTips.h"
#include "DisplayManager.h"
///信息提示基类
class CDisplayTips
{
public:
	void DisplayTips(CTipsElementProduct &tipsProduct,ERRORMSGINDEX errorIndex);
};
///状态基类，用于派生出CServe、CSpeed等类
class CRobotState:public CDisplayTips
{
public:
	CRobotState();
	virtual void DisplayState(CControlUI* controlText,CControlUI* controlImage)=0;
	int GetState();
protected:
	void SetState(int iflag);
	CCommunication* m_pComm;
private:
	int m_iFlag;
};

class CState
{
public:
	//CState();声明了构造函数，就要调用
	virtual void DisplayState(CControlUI* controlText,CControlUI* controlImage)=0;
	
protected:
	void SetTextAndBkImg(CControlUI* controlText,CStdString strText,CControlUI* controlImage,CStdString strBkimg);
};

///伺服状态显示，开关两种状态
class CServeOnState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

class CServeOffState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

///示教速度状态显示，分别为低中高三种状态
class CSpeedLowState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

class CSpeedMidState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

class CSpeedHighState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};
///机器人坐标状态显示，分为直角、关节、工具、用户
class CCoordCartState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

class CCoordJointState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

class CCoordToolState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};
class CCoordUserState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

///机器人同步状态显示
class CSyncState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

class CUnsyncState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};
///机器人对象状态显示
class CRobotBaseState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

class CRobotPosState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

///机器人模式状态显示
class CModelTeachState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};

class CModelReplayState:public CState
{
public:
	void DisplayState(CControlUI* controlText,CControlUI* controlImage);
};


