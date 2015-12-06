/**
*@file
*文件名称：CLoginWnd.cpp
*
*摘要：登录窗口
*
*@author fly1992@163.com
*
**/
#include "LoginWnd.h"
#include "CHandleWnd.h"
CLoginWnd::CLoginWnd()
{ 

}
/**
*@brief 设置窗口名称
*函数名称：GetWindowClassName
*函数功能：设置窗口名称
**/
LPCTSTR CLoginWnd::GetWindowClassName() const
{ 
	return _T("UILoginFrame"); 
}
/**
*@brief 设置窗口类型
*函数名称：GetClassStyle
*函数功能：设置窗口类型
**/
UINT CLoginWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_DIALOG;                     
}
/**
*@brief 窗口关闭前最后处理的消息
*函数名称：OnFinalMessage
*函数功能：窗口关闭前最后处理的消息
**/
void CLoginWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}
/**
*@brief 创建窗口之后的初始化工作
*函数名称：Init
*函数功能：创建窗口之后的初始化工作
**/
void CLoginWnd::Init() 
{
	m_HostIPEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("HostIP")));
	m_OkBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("OkBtn")));
	m_CancleBtn=static_cast<CButtonUI*>(m_pm.FindControl(_T("CancleBtn")));
	m_pComboUI = static_cast<CComboUI*>(m_pm.FindControl(_T("ComboOperator")));
	m_OkBtn->SetFocus();
}
/**
*@brief 捕获各类窗口消息
*函数名称：Notify
*函数功能：捕获各类窗口消息
**/
void CLoginWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) {
		if( msg.pSender->GetName() == _T("CloseBtn")||msg.pSender->GetName()==_T("CancleBtn"))
		{
			PostQuitMessage(0);
			return; 
		}
		else if( msg.pSender->GetName() == _T("OkBtn") ) 
		{ 
			CTCPClient_CE::GetInstance()->Open();
			if(m_pComboUI->GetCurSel()==0)
			{
	
				//建立与服务器端连接
				if (m_HostIPEdit->GetText()==_T("LAB408")&&CTCPClient_CE::GetInstance()->Connect())
				{
					HwndHandle::pDisplayTips->DisplayTips(CTips::tipsInfoProduct,OPERATOR_LOGIN_SUCCESS);
					USLM=OPERATOR;
					Close();
				}
				else
				{
					MessageBox(NULL,_T("操作员登录失败！"),_T("提示"),MB_OK);
					return;
				}
			}
			else if (m_pComboUI->GetCurSel()==1)
			{
				//建立与服务器端连接
				if (m_HostIPEdit->GetText()==_T("LAB408")&&CTCPClient_CE::GetInstance()->Connect())
				{
					HwndHandle::pDisplayTips->DisplayTips(CTips::tipsInfoProduct,ADMIN_LOGIN_SUCCESS);
					USLM=ADMIN;
					Close();
				}
				else
				{
					MessageBox(NULL,_T("管理员登录失败！"),_T("提示"),MB_OK);
					return;
				}
			}
			return; 
		}
	}
	else if ( msg.sType == _T("setfocus"))
	{
		if ( msg.pSender->GetName() == _T("HostIP"))
		{
			::ShowWindow(KeyPadWnd::GetHandle(m_hWnd)->GetHWND(),SW_SHOW);
		}
	}
}
/**
*@brief 加载XML文件，创建窗口
*函数名称：OnCreate
*函数功能：加载XML文件，创建窗口
**/
LRESULT CLoginWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("HostNameWnd.xml"), (UINT)0, (UINT)0, &m_pm);
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
LRESULT CLoginWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT  CLoginWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return FALSE;
}
/**
*@brief 软键盘消息处理函数
*函数名称：OnInputKeyEdit
*函数功能：软键盘消息处理函数
**/
LRESULT CLoginWnd::OnInputKeyEdit(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CStdString *m_StrEdit=(CStdString*)wParam;
	m_HostIPEdit->SetText(*m_StrEdit);
	delete m_StrEdit;
	return TRUE;
}