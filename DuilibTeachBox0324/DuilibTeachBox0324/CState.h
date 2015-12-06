/**
*@file
*�ļ����ƣ�CState.h
*
*ժҪ��״̬���࣬����������������״̬�࣬���״̬�л�
*
*@author fly1992@163.com
*
**/
#pragma once
#include "GlobalVar.h"
#include "CCommunication.h"
#include "CTips.h"
#include "DisplayManager.h"
///��Ϣ��ʾ����
class CDisplayTips
{
public:
	void DisplayTips(CTipsElementProduct &tipsProduct,ERRORMSGINDEX errorIndex);
};
///״̬���࣬����������CServe��CSpeed����
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
	//CState();�����˹��캯������Ҫ����
	virtual void DisplayState(CControlUI* controlText,CControlUI* controlImage)=0;
	
protected:
	void SetTextAndBkImg(CControlUI* controlText,CStdString strText,CControlUI* controlImage,CStdString strBkimg);
};

///�ŷ�״̬��ʾ����������״̬
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

///ʾ���ٶ�״̬��ʾ���ֱ�Ϊ���и�����״̬
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
///����������״̬��ʾ����Ϊֱ�ǡ��ؽڡ����ߡ��û�
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

///������ͬ��״̬��ʾ
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
///�����˶���״̬��ʾ
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

///������ģʽ״̬��ʾ
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


