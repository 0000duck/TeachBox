/**
*@file
*�ļ����ƣ�CInsertWnd.h
*ժҪ������ָ���
*@author fly1992@163.com
**/
#pragma once
#include "GlobalVar.h"
///���봰����
class CInsertWnd : public CWindowWnd, public INotifyUI, public IMessageFilterUI
{
public:
	CInsertWnd();
	LPCTSTR GetWindowClassName() const ;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/) ;
	void Init() ;
	void Notify(TNotifyUI& msg);
	void AddMacroListItem(TCHAR *temp);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnInputKeyEdit(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CPaintManagerUI m_pm;
private:
	CTreeViewUI* m_TreeView;
	CListUI * m_MacroListUI;
};