/**
*@file
*�ļ����ƣ�CNewFileWnd.h
*
*ժҪ���½���ҵ�ļ�����
*
*@author fly1992@163.com
*
**/
#pragma once
#include "GlobalVar.h"
///�½���ҵ�ļ�������
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
	CEditUI* m_ProgramNameEdit;///<��ҵ�ļ����ֱ༭��
	CEditUI* m_ProgramNoteEdit;///<��ҵ�ļ�ע�ͱ༭��
private:
	CButtonUI* m_NewFileBtn;
	int m_EditFlag;
};