/**
*@file
*文件名称：MainUI.h
*
*摘要：人机交互主窗口
*
*@author fly1992@163.com
*
**/
#pragma once
#include "GlobalVar.h"
#include "CRobot.h"
#include "Control.h"
#include "CFileButtonState.h"
#include "CRobotJob.h"
///主窗口类，处理人机交互信息
class CMainFrameRobotDlg : public CWindowWnd, public INotifyUI, public IMessageFilterUI
{
public:
	CMainFrameRobotDlg(void);
	~CMainFrameRobotDlg(void);
	LPCTSTR GetWindowClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam); 
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	void Notify(TNotifyUI& msg);
	void Init();
	void OnWindowInit();
	void OnLBtnClick(CControlUI *pControl);
	///初始化主界面类中的各种控件，获得对应的指针，方便设置控件的属性
	void InitFileButtonControl();
	void InitStateControl();
	void InitCoordControl();
	void InitComplicateControl();
public:
	friend class TeachBoxKeyHandle;///<友元类，可以实现对象对私有成员的访问
protected:
	CPaintManagerUI m_PaintManager;	///<与控件绘制和消息处理关联起来
public:
	FileButtonControl* m_pFileButtonControl;///<使用没有分配空间的指针，弱智
	StateControl* m_pStateControl;///<状态控件结构体
	CoordControl* m_pCoordControl;///<坐标控件结构体

	CComboUI* m_pComboError;///<错误信息显示组合框
	CListUIEx *m_pRobotList;///<作业文件显示列表
	CListHeaderItemUI* m_pListHeaderItem;///<作业文件显示列表头
	CRobot *m_pRobot;///<伺服类，实现信息传送，伺服控制，状态切换
	CFileButtonState *m_pFileButtonState;///<设置按钮状态类指针
	CJobDisplay* m_pJobDisplay;///<机器人作业文件显示类指针

};
///声明物理按键类，用于处理物理按键的响应
class TeachBoxKeyHandle
{
private:
	///定义示教盒物理按键的个数
	enum {KEYNUMBER=31,NEWFILE,PROJECT,START};
public:
	TeachBoxKeyHandle(CMainFrameRobotDlg* pMain);
	void KeyMessageHandle(int ikeyValue);
	void ServeHandle(void*);
	void SpeedHandle(void*);
	void CoordHandle(void*);
	void SyncHandle(void*);
	void RobotObjHandle(void*);
	void NewFileHandle(void*);
	void ProjectHandle(void*);
	void AxisControlHandle(void*);
	void TcpConnect(void*);
	void ModelHandle(void*);
	void StartHandle(void*);
	void StepHandle(void*);
	void ShutDownHandle1(void*);
	void ShutDownHandle2(void*);
	static TeachBoxKeyHandle* GetHandle(CMainFrameRobotDlg* pMain);

private:
	bool m_bflag1;///<区分物理按键，newfile和project
	bool m_bflag2;///<辨别newfile和project是否是第一次按下
	bool m_bKeyUpFlag;
	bool m_bShutDow;
	CMainFrameRobotDlg* m_pMainUI;
	///获取物理按键的在数组指针中的索引号
	int GetTeachBoxKeyIndex(int keyValue);
	///物理按键对应的按键响应函数数组指针，指明函数所属作用域TeachBoxKeyHandle
	void (TeachBoxKeyHandle::*KeyHandle[KEYNUMBER])(void*);
	void CreateMapKeyHandle(void);
	static TeachBoxKeyHandle* teachBoxHandle;
};

