/**
*@file
*�ļ����ƣ�CLoginWnd.h
*
*ժҪ����¼����
*
*@author fly1992@163.com
*
**/
#pragma once
#include "GlobalVar.h"
class CLoginWnd : public CWindowWnd, public INotifyUI, public IMessageFilterUI
{
public:
	CLoginWnd();
	LPCTSTR GetWindowClassName() const ;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/) ;
	void Init() ;
	void Notify(TNotifyUI& msg);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnInputKeyEdit(UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	CPaintManagerUI m_pm;
private:
	CButtonUI* m_OkBtn;
	CButtonUI* m_CancleBtn;
	CEditUI* m_HostIPEdit;///<��������༭��
	CComboUI* m_pComboUI;///<��Ͽ��û�ѡ���û�����
};