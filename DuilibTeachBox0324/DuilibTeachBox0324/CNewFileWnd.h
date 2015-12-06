/**
*@file
*文件名称：CNewFileWnd.h
*
*摘要：新建作业文件窗口
*
*@author fly1992@163.com
*
**/
#pragma once
#include "GlobalVar.h"
///新建作业文件窗口类
class CNewFileWnd : public CWindowWnd, public INotifyUI, public IMessageFilterUI
{
public:
	CNewFileWnd();
	LPCTSTR GetWindowClassName() const ;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/) ;
	void Init() ;
	void Notify(TNotifyUI& msg);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnInputKeyEdit(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	CPaintManagerUI m_pm;
	CStdString m_ProgramName;
public:
	CEditUI* m_ProgramNameEdit;///<作业文件名字编辑框
	CEditUI* m_ProgramNoteEdit;///<作业文件注释编辑框
private:
	CButtonUI* m_NewFileBtn;
	int m_EditFlag;
};