/**
*@file
*文件名称：CMovlWnd.h
*
*摘要：Movl指令窗口
*
*@author fly1992@163.com
*
**/
#pragma  once
#include "InstrucionHeader.h"
class CMovlWnd : public CWindowWnd, public INotifyUI, public IMessageFilterUI
{
public:
	CMovlWnd();
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
	CEditUI* m_pMovlPos;
	CEditUI* m_pMovlSpeed;
	CEditUI* m_pMovlPL;
	CLabelUI* m_pMovlAll;
	CStrInstuction m_InstrMovl;///<Movl指令
	int m_iFlagEdit;///<当前获取的光标的编辑框标志
};