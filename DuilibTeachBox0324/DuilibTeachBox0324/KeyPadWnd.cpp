/**
*@file
*文件名称：KeyPadWnd.cpp
*
*摘要：软键盘窗口
*
*@author fly1992@163.com
*
**/
#include "KeyPadWnd.h"
KeyPadWnd* KeyPadWnd::keyPadWnd=NULL;
/**
*@brief 获取软键盘窗口指针
*函数名称：GetHandle
*函数功能：获取软键盘窗口指针
**/
KeyPadWnd* KeyPadWnd::GetHandle(HWND hwnd)
{
	if (keyPadWnd==NULL)
	{
		keyPadWnd=new KeyPadWnd;
	}
	keyPadWnd->m_KeyPadHandle=hwnd;
	return keyPadWnd;
}

KeyPadWnd::KeyPadWnd() 
{
	m_pEditStr=_T("");
	m_pCapsLock=CAPITAL;
}
/**
*@brief 设置窗口名称
*函数名称：GetWindowClassName
*函数功能：设置窗口名称
**/
LPCTSTR KeyPadWnd::GetWindowClassName() const 
{ 
	return _T("KeyPadWndUI");
}
/**
*@brief 设置窗口类型
*函数名称：GetClassStyle
*函数功能：设置窗口类型
**/
UINT KeyPadWnd::GetClassStyle() const 
{ 
	return CS_DBLCLKS;
}
/**
*@brief 窗口关闭前最后处理的消息
*函数名称：OnFinalMessage
*函数功能：窗口关闭前最后处理的消息
**/
void KeyPadWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	delete this; 
}

void KeyPadWnd::Init() 
{


}
/**
*@brief 创建窗口之后的初始化工作
*函数名称：OnPrepare
*函数功能：创建窗口之后的初始化工作
**/
void KeyPadWnd::OnPrepare() 
{
	m_pInputEdit=static_cast<CEditUI*>(m_pm.FindControl(_T("InputEdit")));
	KeyLetterInit();
	KeyNumberInit();
	KeyFunctionInit();
}
/**
*@brief 捕获各类窗口消息
*函数名称：Notify
*函数功能：捕获各类窗口消息
**/
void KeyPadWnd::Notify(TNotifyUI& msg)
{
	CStdString KeyStr=msg.pSender->GetName();
	if( msg.sType == _T("windowinit") ) OnPrepare();
	else if( msg.sType == _T("click") ) 
	{
		SelectkeyFunction(KeyStr);
		SelectKeyLetter(KeyStr);
		SelectKeyNumber(KeyStr);
		m_pInputEdit->SetText(m_pEditStr);
	}
	else if(msg.sType==_T("selectchanged"))
	{
		CStdString name = msg.pSender->GetName();
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("switch")));
		if(name==_T("KeyBoard"))
		{
			pControl->SelectItem(0);

		}
		else if(name==_T("Symbol"))
		{
			pControl->SelectItem(1);
		}
	}
}
/**
*@brief 加载XML文件，创建窗口
*函数名称：OnCreate
*函数功能：加载XML文件，创建窗口
**/
LRESULT KeyPadWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;

	CControlUI* pRoot = builder.Create(_T("KeyBoardAll.xml"), (UINT)0,  &cb, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	Init();
	m_pm.AddNotifier(this);


	return 0;
}

LRESULT KeyPadWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT KeyPadWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);

	bHandled = FALSE;
	return 0;
}
/**
*@brief windows消息处理函数
*函数名称：HandleMessage
*函数功能：windows消息处理函数
**/
LRESULT KeyPadWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg )
	{
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;		
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}
/**
*@brief 将按下的字母按键，并保存显示到编辑框中
*函数名称：SelectKeyLetter
*函数功能：将按下字母的按键，并保存显示到编辑框中
**/
void KeyPadWnd::SelectKeyLetter(CStdString KeyStr)
{

	if (KeyStr==KEYA)
	{
		m_pEditStr+=(m_pCapsLock!=SMALL)?_T("a"):_T("A");
		return;
	}
	else if (KeyStr==KEYB)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("b"):_T("B");
		return;
	}
	else if (KeyStr==KEYC)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("c"):_T("C");
		return;
	}
	else if (KeyStr==KEYD)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("d"):_T("D");
		return;
	}
	else if (KeyStr==KEYE)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("e"):_T("E");
		return;
	}
	else if (KeyStr==KEYF)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("f"):_T("F");
		return;
	}
	else if (KeyStr==KEYG)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("g"):_T("G");
		return;
	}
	else if (KeyStr==KEYH)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("h"):_T("H");
		return;
	}
	else if (KeyStr==KEYI)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("i"):_T("I");
		return;
	}
	else if (KeyStr==KEYJ)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("j"):_T("J");
		return;
	}
	else if (KeyStr==KEYK)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("k"):_T("K");
		return;
	}
	else if (KeyStr==KEYL)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("l"):_T("L");
		return;
	}
	else if (KeyStr==KEYM)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("m"):_T("M");
		return;
	}
	else if (KeyStr==KEYN)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("n"):_T("N");
		return;
	}
	else if (KeyStr==KEYO)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("o"):_T("O");
		return;

	}
	else if (KeyStr==KEYP)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("p"):_T("P");
		return;
	}
	else if (KeyStr==KEYQ)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("q"):_T("Q");
		return;
	}
	else if (KeyStr==KEYR)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("r"):_T("R");
		return;
	}
	else if (KeyStr==KEYS)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("s"):_T("S");
		return;
	}
	else if (KeyStr==KEYT)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("t"):_T("T");
		return;
	}
	else if (KeyStr==KEYU)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("u"):_T("U");
		return;
	}
	else if (KeyStr==KEYV)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("v"):_T("V");
		return;
	}
	else if (KeyStr==KEYW)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("w"):_T("W");
		return;
	}
	else if (KeyStr==KEYX)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("x"):_T("X");
		return;
	}
	else if (KeyStr==KEYY)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("y"):_T("Y");
		return;
	}
	else if (KeyStr==KEYZ)
	{
		m_pEditStr+=(m_pCapsLock)!=SMALL?_T("z"):_T("Z");
		return;
	}
}
/**
*@brief 将按下的数字按键，并保存显示到编辑框中
*函数名称：SelectKeyNumber
*函数功能：将按下数字按键，并保存显示到编辑框中
**/
void KeyPadWnd::SelectKeyNumber(CStdString KeyStr)
{
	if (KeyStr==KEY0)
	{
		m_pEditStr+=_T("0");
		return;
	}
	else if (KeyStr==KEY1)
	{
		m_pEditStr+=_T("1");
		return;
	}
	else if (KeyStr==KEY2)
	{
		m_pEditStr+=_T("2");
		return;
	}
	else if (KeyStr==KEY3)
	{
		m_pEditStr+=_T("3");
		return;
	}
	else if (KeyStr==KEY4)
	{
		m_pEditStr+=_T("4");
		return;
	}
	else if (KeyStr==KEY5)
	{
		m_pEditStr+=_T("5");
		return;
	}
	else if (KeyStr==KEY6)
	{
		m_pEditStr+=_T("6");
		return;
	}
	else if (KeyStr==KEY7)
	{
		m_pEditStr+=_T("7");
		return;
	}
	else if (KeyStr==KEY8)
	{
		m_pEditStr+=_T("8");
		return;
	}
	else if (KeyStr==KEY9)
	{
		m_pEditStr+=_T("9");
		return;
	}
}

void KeyPadWnd::SelectkeyFunction(CStdString KeyStr)
{
	if( KeyStr==KEYCANCEL) 
	{
		m_pEditStr=_T("");
		ShowWindow(false);
		return; 
	}
	else if (KeyStr==KEYCAPSLOCK)
	{
		if (m_pCapsLock==CAPITAL)
		{
			SetCapsLock(CAPITAL);
			m_pCapsLock=SMALL;
			m_pKeyCapsLock->SetNormalImage(_T("KeyDButtonHot.bmp"));
		}
		else if (m_pCapsLock==SMALL)
		{
			SetCapsLock(SMALL);	
			m_pCapsLock=CAPITAL;
			m_pKeyCapsLock->SetNormalImage(_T("KeyDButtonNormal.bmp"));
		}
		return;
	}
	else if (KeyStr==KEYSPACE)
	{
		m_pEditStr+=_T(" ");
		return;
	}
	else if (KeyStr==KEYBACKSPACE)
	{
		if(!m_pEditStr.IsEmpty())
		{
			m_pEditStr.SetAt(m_pEditStr.GetLength()-1,_T('\0'));
		}
		return;
	}
	else if (KeyStr==KEYENTER)
	{
		CStdString *TempStr=new CStdString(m_pEditStr);
		if (m_KeyPadHandle!=NULL)
		{
			::PostMessage(m_KeyPadHandle,WM_INPUTEDIT,(WPARAM)TempStr,0L);
		}
		m_pEditStr=_T("");//此处指针已经清空，所以传过去的字符串自然为空
		ShowWindow(false);
		return;
	}
}
///设置大小写
void KeyPadWnd::SetCapsLock(CAPSLOCK cap)
{
	switch(cap)
	{
	case CAPITAL:
		m_pKeyA->SetText(_T("A"));
		m_pKeyB->SetText(_T("B"));
		m_pKeyC->SetText(_T("C"));
		m_pKeyD->SetText(_T("D"));
		m_pKeyE->SetText(_T("E"));
		m_pKeyF->SetText(_T("F"));
		m_pKeyG->SetText(_T("G"));
		m_pKeyH->SetText(_T("H"));
		m_pKeyI->SetText(_T("I"));
		m_pKeyJ->SetText(_T("J"));
		m_pKeyK->SetText(_T("K"));
		m_pKeyL->SetText(_T("L"));
		m_pKeyM->SetText(_T("M"));
		m_pKeyN->SetText(_T("N"));
		m_pKeyO->SetText(_T("O"));
		m_pKeyP->SetText(_T("P"));
		m_pKeyQ->SetText(_T("Q"));
		m_pKeyR->SetText(_T("R"));
		m_pKeyS->SetText(_T("S"));
		m_pKeyT->SetText(_T("T"));
		m_pKeyU->SetText(_T("U"));
		m_pKeyV->SetText(_T("V"));
		m_pKeyW->SetText(_T("W"));
		m_pKeyX->SetText(_T("X"));
		m_pKeyY->SetText(_T("Y"));
		m_pKeyZ->SetText(_T("Z"));
		break;

	case SMALL:
		m_pKeyA->SetText(_T("a"));
		m_pKeyB->SetText(_T("b"));
		m_pKeyC->SetText(_T("c"));
		m_pKeyD->SetText(_T("d"));
		m_pKeyE->SetText(_T("e"));
		m_pKeyF->SetText(_T("f"));
		m_pKeyG->SetText(_T("g"));
		m_pKeyH->SetText(_T("h"));
		m_pKeyI->SetText(_T("i"));
		m_pKeyJ->SetText(_T("j"));
		m_pKeyK->SetText(_T("k"));
		m_pKeyL->SetText(_T("l"));
		m_pKeyM->SetText(_T("m"));
		m_pKeyN->SetText(_T("n"));
		m_pKeyO->SetText(_T("o"));
		m_pKeyP->SetText(_T("p"));
		m_pKeyQ->SetText(_T("q"));
		m_pKeyR->SetText(_T("r"));
		m_pKeyS->SetText(_T("s"));
		m_pKeyT->SetText(_T("t"));
		m_pKeyU->SetText(_T("u"));
		m_pKeyV->SetText(_T("v"));
		m_pKeyW->SetText(_T("w"));
		m_pKeyX->SetText(_T("x"));
		m_pKeyY->SetText(_T("y"));
		m_pKeyZ->SetText(_T("z"));
		break;
	}
}
///字母按键初始化
void KeyPadWnd::KeyLetterInit()
{
	m_pKeyA=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keya")));
	m_pKeyB=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyb")));
	m_pKeyC=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyc")));
	m_pKeyD=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyd")));
	m_pKeyE=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keye")));
	m_pKeyF=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyf")));
	m_pKeyG=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyg")));
	m_pKeyH=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyh")));
	m_pKeyI=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyi")));
	m_pKeyJ=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyj")));
	m_pKeyK=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyk")));
	m_pKeyL=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyl")));
	m_pKeyM=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keym")));
	m_pKeyN=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyn")));
	m_pKeyO=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyo")));
	m_pKeyP=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyp")));
	m_pKeyQ=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyq")));
	m_pKeyR=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyr")));
	m_pKeyS=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keys")));
	m_pKeyT=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyt")));
	m_pKeyU=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyu")));
	m_pKeyV=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyv")));
	m_pKeyW=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyw")));
	m_pKeyX=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyx")));
	m_pKeyY=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyy")));
	m_pKeyZ=static_cast<CButtonUI*>(m_pm.FindControl(_T("Keyz")));



}
///数字按键初始化
void KeyPadWnd::KeyNumberInit()
{
	m_pKey0=static_cast<CButtonUI*>(m_pm.FindControl(_T("Key0")));
	m_pKey1=static_cast<CButtonUI*>(m_pm.FindControl(_T("Key1")));
	m_pKey2=static_cast<CButtonUI*>(m_pm.FindControl(_T("Key2")));
	m_pKey3=static_cast<CButtonUI*>(m_pm.FindControl(_T("Key3")));
	m_pKey4=static_cast<CButtonUI*>(m_pm.FindControl(_T("Key4")));
	m_pKey5=static_cast<CButtonUI*>(m_pm.FindControl(_T("Key5")));
	m_pKey6=static_cast<CButtonUI*>(m_pm.FindControl(_T("Key6")));
	m_pKey7=static_cast<CButtonUI*>(m_pm.FindControl(_T("Key7")));
	m_pKey8=static_cast<CButtonUI*>(m_pm.FindControl(_T("Key8")));
	m_pKey9=static_cast<CButtonUI*>(m_pm.FindControl(_T("Key9")));

}
///控制按键初始化
void KeyPadWnd::KeyFunctionInit()
{

	m_pKeyCancle=static_cast<CButtonUI*>(m_pm.FindControl(_T("KeyCancel")));
	m_pKeyEnter=static_cast<CButtonUI*>(m_pm.FindControl(_T("KeyEnter")));
	m_pKeyCapsLock=static_cast<CButtonUI*>(m_pm.FindControl(_T("KeyCapsLock")));
	m_pKeySpace=static_cast<CButtonUI*>(m_pm.FindControl(_T("KeySpace")));
	m_pKeyBackSpace=static_cast<CButtonUI*>(m_pm.FindControl(_T("KeyBackSpace")));

}

