/**
*@file
*文件名称：CMovlWnd.cpp
*
*摘要：Movl指令窗口
*
*@author fly1992@163.com
*
**/
#include "CMovlWnd.h"
#include "CHandleWnd.h"
CMovlWnd::CMovlWnd():m_InstrMovl(INSTRMOVL)
{ 

}
/**
*@brief 设置窗口名称
*函数名称：GetWindowClassName
*函数功能：设置窗口名称
**/
LPCTSTR CMovlWnd::GetWindowClassName() const
{ 
	return _T("UIMovlWnd"); 
}
/**
*@brief 设置窗口类型
*函数名称：GetClassStyle
*函数功能：设置窗口类型
**/
UINT CMovlWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_DIALOG; 
}
/**
*@brief 窗口关闭前最后处理的消息
*函数名称：OnFinalMessage
*函数功能：窗口关闭前最后处理的消息
**/
void CMovlWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}
/**
*@brief 创建窗口之后的初始化工作
*函数名称：Init
*函数功能：创建窗口之后的初始化工作
**/
void CMovlWnd::Init() 
{
	m_pMovlPos=static_cast<CEditUI*>(m_pm.FindControl(_T("MovlP")));
	m_pMovlSpeed=static_cast<CEditUI*>(m_pm.FindControl(_T("MovlV")));
	m_pMovlPL=static_cast<CEditUI*>(m_pm.FindControl(_T("MovlPL")));
	m_pMovlAll=static_cast<CLabelUI*>(m_pm.FindControl(_T("MovlAll")));
}
/**
*@brief 捕获各类窗口消息
*函数名称：Notify
*函数功能：捕获各类窗口消息
**/
void CMovlWnd::Notify(TNotifyUI& msg)
{

	if ( msg.sType == _T("setfocus"))
	{
		if ( msg.pSender->GetName() == _T("MovlP"))
		{
			m_iFlagEdit=0;
			::ShowWindow(KeyPadWnd::GetHandle(m_hWnd)->GetHWND(),SW_SHOW);
		}
		if ( msg.pSender->GetName() == _T("MovlV"))
		{
			m_iFlagEdit=1;
			::ShowWindow(KeyPadWnd::GetHandle(m_hWnd)->GetHWND(),SW_SHOW);
		}
		if ( msg.pSender->GetName() == _T("MovlPL"))
		{
			m_iFlagEdit=2;
			::ShowWindow(KeyPadWnd::GetHandle(m_hWnd)->GetHWND(),SW_SHOW);
		}

	}	
}
/**
*@brief 加载XML文件，创建窗口
*函数名称：OnCreate
*函数功能：加载XML文件，创建窗口
**/
LRESULT CMovlWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CControlUI* pRoot=NULL;
	pRoot = builder.Create(INSTRMOVL, (UINT)0, (UINT)0, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);
	Init();
	return 0;
}
/**
*@brief windows消息处理函数
*函数名称：HandleMessage
*函数功能：windows消息处理函数
**/
LRESULT CMovlWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg )
	{
	case WM_CREATE:		lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_INPUTEDIT:	lRes = OnInputKeyEdit(uMsg, wParam,lParam);break;
	default:			bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT  CMovlWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return FALSE;
}
/**
*@brief 软键盘消息处理函数
*函数名称：OnInputKeyEdit
*函数功能：软键盘消息处理函数
**/
LRESULT CMovlWnd::OnInputKeyEdit(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CStdString *m_StrEdit=(CStdString*)wParam;
	EditValid *pEditValid=HwndHandle::pEditValid;
	std::string str=Tchar2String(*m_StrEdit);
	switch(m_iFlagEdit)
	{
	case 0:
		if (pEditValid->isValidRobotPos(str))
		{
			m_pMovlPos->SetText(*m_StrEdit);
			m_InstrMovl.SetInstrPos(*m_StrEdit);
			HwndHandle::pDisplayTips->DisplayTips(CTips::tipsInfoProduct,VALID_INPUT);
		}
		else
		{
			//MessageBox(NULL,_T("请输入合理位置/n例如P000"),_T("提示"),MB_OK);
			HwndHandle::pDisplayTips->DisplayTips(CTips::errorInfoProduct,INVALID_POSTION);
			return FALSE;
		}
		break;

	case 1:
		if (pEditValid->isValidSpeed(str))
		{
			m_pMovlSpeed->SetText(*m_StrEdit);
			m_InstrMovl.SetInstrSpeedV(*m_StrEdit);
			HwndHandle::pDisplayTips->DisplayTips(CTips::tipsInfoProduct,VALID_INPUT);
		}
		else
		{
		//	MessageBox(NULL,_T("请输入1-100"),_T("提示"),MB_OK);
			HwndHandle::pDisplayTips->DisplayTips(CTips::errorInfoProduct,INVALID_SPEED);

			return FALSE;;
		}
		break;
	case 2:
		if (pEditValid->isValidPL(str))
		{
			m_pMovlPL->SetText(*m_StrEdit);
			m_InstrMovl.SetInstrPLV(*m_StrEdit);
			HwndHandle::pDisplayTips->DisplayTips(CTips::tipsInfoProduct,VALID_INPUT);
		}
		else
		{
			MessageBox(NULL,_T("请输入0-9"),_T("提示"),MB_OK);
			HwndHandle::pDisplayTips->DisplayTips(CTips::errorInfoProduct,INVALID_PL);
			return FALSE;;
		}
		break;
	default:
		break;
	}
	m_pMovlAll->SetText(m_InstrMovl.GetInstrAll());
	HwndHandle::stdString=m_InstrMovl.GetInstrDisplay();
	delete m_StrEdit;
	return TRUE;
}
