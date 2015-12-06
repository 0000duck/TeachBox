/**
*@file
*�ļ����ƣ�MainUI.h
*
*ժҪ���˻�����������
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
///�������࣬�����˻�������Ϣ
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
	///��ʼ�����������еĸ��ֿؼ�����ö�Ӧ��ָ�룬�������ÿؼ�������
	void InitFileButtonControl();
	void InitStateControl();
	void InitCoordControl();
	void InitComplicateControl();
public:
	friend class TeachBoxKeyHandle;///<��Ԫ�࣬����ʵ�ֶ����˽�г�Ա�ķ���
protected:
	CPaintManagerUI m_PaintManager;	///<��ؼ����ƺ���Ϣ�����������
public:
	FileButtonControl* m_pFileButtonControl;///<ʹ��û�з���ռ��ָ�룬����
	StateControl* m_pStateControl;///<״̬�ؼ��ṹ��
	CoordControl* m_pCoordControl;///<����ؼ��ṹ��

	CComboUI* m_pComboError;///<������Ϣ��ʾ��Ͽ�
	CListUIEx *m_pRobotList;///<��ҵ�ļ���ʾ�б�
	CListHeaderItemUI* m_pListHeaderItem;///<��ҵ�ļ���ʾ�б�ͷ
	CRobot *m_pRobot;///<�ŷ��࣬ʵ����Ϣ���ͣ��ŷ����ƣ�״̬�л�
	CFileButtonState *m_pFileButtonState;///<���ð�ť״̬��ָ��
	CJobDisplay* m_pJobDisplay;///<��������ҵ�ļ���ʾ��ָ��

};
///�����������࣬���ڴ�������������Ӧ
class TeachBoxKeyHandle
{
private:
	///����ʾ�̺��������ĸ���
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
	bool m_bflag1;///<������������newfile��project
	bool m_bflag2;///<���newfile��project�Ƿ��ǵ�һ�ΰ���
	bool m_bKeyUpFlag;
	bool m_bShutDow;
	CMainFrameRobotDlg* m_pMainUI;
	///��ȡ��������������ָ���е�������
	int GetTeachBoxKeyIndex(int keyValue);
	///��������Ӧ�İ�����Ӧ��������ָ�룬ָ����������������TeachBoxKeyHandle
	void (TeachBoxKeyHandle::*KeyHandle[KEYNUMBER])(void*);
	void CreateMapKeyHandle(void);
	static TeachBoxKeyHandle* teachBoxHandle;
};

