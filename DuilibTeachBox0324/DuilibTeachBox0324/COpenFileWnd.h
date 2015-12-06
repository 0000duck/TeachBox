/**
*@file
*文件名称：COpenFileWnd.cpp
*
*摘要：选择机器人作业文件窗口
*
*@author fly1992@163.com
*
**/
#pragma once
#include <vector>
#include "GlobalVar.h"
///作业文件窗口类
class COpenFileWnd : public CWindowWnd, public INotifyUI, public IMessageFilterUI
{
public:
	COpenFileWnd();
	LPCTSTR GetWindowClassName() const ;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/) ;
	void Init() ;
	void Notify(TNotifyUI& msg);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	void AddFileListItem(LPCTSTR temp);
	void RemoveAllListItem();
	CStdString GetListItemText(CControlUI* pcontrol);
	void AddAllFileListItem(std::vector<TSTRING> &vecStr);
	void SelectCurrentListItem();
public:
	CPaintManagerUI m_pm;
	CListUI* m_FileNameList;///<添加作业文件列表

private:
	CStdString m_ListItemText;
	int m_iGetItemIndex;
};