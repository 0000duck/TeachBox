/**
*@file
*文件名称：CMovjWnd.h
*
*摘要：Movj指令窗口
*
*@author fly1992@163.com
*
**/
#pragma  once
#include "InstrucionHeader.h"
class CMovjWnd : public CWindowWnd, public INotifyUI, public IMessageFilterUI
{
public:
	CMovjWnd();
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
	CEditUI* m_pMovjPos;
	CEditUI* m_pMovjSpeed;
	CEditUI* m_pMovjPL;
	CLabelUI* m_pMovjAll;
	CStrInstuction m_InstrMovj;///<Movj指令
	int m_iFlagEdit;///<当前获取的光标的编辑框标志
};