/**
*@file
*�ļ����ƣ�CMovcWnd.h
*
*ժҪ��Movcָ���
*
*@author fly1992@163.com
*
**/
#pragma  once
#include "InstrucionHeader.h"
class CMovcWnd : public CWindowWnd, public INotifyUI, public IMessageFilterUI
{
public:
	CMovcWnd();
	LPCTSTR GetWindowClassName() const ;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/) ;
	void Init();
	void Notify(TNotifyUI& msg);
	LRESULT OnInputKeyEdit(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
public:
	CPaintManagerUI m_pm;
private:
	CEditUI* m_pMovcPos;
	CEditUI* m_pMovcSpeed;
	CEditUI* m_pMovcPL;
	CLabelUI* m_pMovcAll;
	CStrInstuction m_InstrMovc;///<Movcָ��
	int m_iFlagEdit;///<��ǰ��ȡ�Ĺ��ı༭���־
};