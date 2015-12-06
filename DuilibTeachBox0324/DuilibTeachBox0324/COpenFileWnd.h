/**
*@file
*�ļ����ƣ�COpenFileWnd.cpp
*
*ժҪ��ѡ���������ҵ�ļ�����
*
*@author fly1992@163.com
*
**/
#pragma once
#include <vector>
#include "GlobalVar.h"
///��ҵ�ļ�������
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
	CListUI* m_FileNameList;///<�����ҵ�ļ��б�

private:
	CStdString m_ListItemText;
	int m_iGetItemIndex;
};