/**
*@file
*文件名称：KeyPadWnd.h
*
*摘要：软键盘窗口
*
*@author fly1992@163.com
*
**/
#pragma once
#include "GlobalVar.h"
#include "KeyBoard.h"
#include "KeyTable.h"
#define  WM_INPUTEDIT (WM_USER+103)///<发送字符的窗口消息
///软键盘窗口类
class KeyPadWnd : public CWindowWnd, public INotifyUI
{
public:
	KeyPadWnd();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const ;
	void OnFinalMessage(HWND /*hWnd*/);
	void Init();
	void OnPrepare() ;
	void Notify(TNotifyUI& msg);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void KeyLetterInit();
	void KeyNumberInit();
	void KeyFunctionInit();
	void SetCapsLock(CAPSLOCK cap);
	void SelectKeyNumber(CStdString KeyStr);
	void SelectKeyLetter(CStdString KeyStr);
	void SelectkeyFunction(CStdString KeyStr);
	static KeyPadWnd* GetHandle(HWND hwnd); 
	HWND m_KeyPadHandle;///<设置键盘中的字符要发送的窗口的句柄
	static KeyPadWnd* keyPadWnd;
public:
	CPaintManagerUI m_pm;
private:
	CEditUI *m_pInputEdit;
private:

	CButtonUI* m_pKey1;
	CButtonUI* m_pKey2;
	CButtonUI* m_pKey3;
	CButtonUI* m_pKey4;
	CButtonUI* m_pKey5;
	CButtonUI* m_pKey6;
	CButtonUI* m_pKey7;
	CButtonUI* m_pKey8;
	CButtonUI* m_pKey9;
	CButtonUI* m_pKey0;

	CButtonUI* m_pKeyA;
	CButtonUI* m_pKeyB;
	CButtonUI* m_pKeyC;
	CButtonUI* m_pKeyD;
	CButtonUI* m_pKeyE;
	CButtonUI* m_pKeyF;
	CButtonUI* m_pKeyG;
	CButtonUI* m_pKeyH;
	CButtonUI* m_pKeyI;
	CButtonUI* m_pKeyJ;
	CButtonUI* m_pKeyK;
	CButtonUI* m_pKeyL;
	CButtonUI* m_pKeyM;
	CButtonUI* m_pKeyN;
	CButtonUI* m_pKeyO;
	CButtonUI* m_pKeyP;
	CButtonUI* m_pKeyQ;
	CButtonUI* m_pKeyR;
	CButtonUI* m_pKeyS;
	CButtonUI* m_pKeyT;
	CButtonUI* m_pKeyU;
	CButtonUI* m_pKeyV;
	CButtonUI* m_pKeyW;
	CButtonUI* m_pKeyX;
	CButtonUI* m_pKeyY;
	CButtonUI* m_pKeyZ;

	CButtonUI* m_pKeyEnter;
	CButtonUI* m_pKeySpace;
	CButtonUI* m_pKeyBackSpace;
	CButtonUI* m_pKeyCancle;
	CButtonUI* m_pKeyCapsLock;

	CAPSLOCK m_pCapsLock;
	CStdString m_pEditStr;
};
