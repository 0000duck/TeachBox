/**
*@file
*文件名称：CInsertWnd.cpp
*摘要：插入指令窗口
*@author fly1992@163.com
**/
#include "CInsertWnd.h"
#include "CHandleWnd.h"
CInsertWnd::CInsertWnd()
{ 

}
/**
*@brief 设置窗口名称
*函数名称：GetWindowClassName
*函数功能：设置窗口名称
**/
LPCTSTR CInsertWnd::GetWindowClassName() const
{ 
	return _T("UIInsertFrame"); 
}
/**
*@brief 设置窗口类型
*函数名称：GetClassStyle
*函数功能：设置窗口类型
**/
UINT CInsertWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_DIALOG; 
}
/**
*@brief 窗口关闭前最后处理的消息
*函数名称：OnFinalMessage
*函数功能：窗口关闭前最后处理的消息
**/
void CInsertWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}
/**
*@brief 创建窗口之后的初始化工作
*函数名称：Init
*函数功能：创建窗口之后的初始化工作
**/
void CInsertWnd::Init() 
{
	m_TreeView=static_cast<CTreeViewUI*>(m_pm.FindControl(_T("RobotTreeView")));
	m_MacroListUI=static_cast<CListUI*>(m_pm.FindControl(_T("Macrolist")));

	HwndHandle::pMovjWnd=new CMovjWnd;///<创建MOVJ窗口
	HwndHandle::pMovjWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0,1,0, 0, 0, NULL);
	::ShowWindow(*HwndHandle::pMovjWnd,SW_HIDE);

	HwndHandle::pMovlWnd=new CMovlWnd;///<创建MOVl窗口
	HwndHandle::pMovlWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0,1,0, 0, 0, NULL);
	::ShowWindow(*HwndHandle::pMovlWnd,SW_HIDE);

	HwndHandle::pMovcWnd=new CMovcWnd;///<创建MOVc窗口
	HwndHandle::pMovcWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0,1,0, 0, 0, NULL);
	::ShowWindow(*HwndHandle::pMovcWnd,SW_HIDE);
}
/**
*@brief 捕获各类窗口消息
*函数名称：Notify
*函数功能：捕获各类窗口消息
**/
void CInsertWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType==_T("itemactivate"))
	{
		if(msg.pSender->GetName()==_T("Movement"))
		{
			m_MacroListUI->RemoveAll();
			AddMacroListItem(_T("MOVJ"));
			AddMacroListItem(_T("MOVL"));
			AddMacroListItem(_T("MOVC"));
		}
		else if (msg.pSender->GetName()==_T("TimeMeasurement"))
		{
			m_MacroListUI->RemoveAll();
			AddMacroListItem(_T("TIME1"));
			AddMacroListItem(_T("TIME2"));
			AddMacroListItem(_T("TIME3"));
		}
		else if (msg.pSender->GetText()==_T("MOVJ"))
		{
			::ShowWindow(*HwndHandle::pMovjWnd,SW_SHOW);
			HwndHandle::pMainFrameRobotDlg->m_pFileButtonState->ChangeButtonState(_T("确定"));
		}
		else if (msg.pSender->GetText()==_T("MOVL"))
		{
			::ShowWindow(*HwndHandle::pMovlWnd,SW_SHOW);
			HwndHandle::pMainFrameRobotDlg->m_pFileButtonState->ChangeButtonState(_T("确定"));
		}
		else if (msg.pSender->GetText()==_T("MOVC"))
		{
			::ShowWindow(*HwndHandle::pMovcWnd,SW_SHOW);
			HwndHandle::pMainFrameRobotDlg->m_pFileButtonState->ChangeButtonState(_T("确定"));
		}
	}
}
/**
*@brief 加载XML文件，创建窗口
*函数名称：OnCreate
*函数功能：加载XML文件，创建窗口
**/
LRESULT CInsertWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("RobotOrder1.xml"), (UINT)0, (UINT)0, &m_pm);
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
LRESULT CInsertWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg )
	{
	case WM_CREATE:		lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;

	default:			bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}
LRESULT  CInsertWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return FALSE;
}
/**
*@brief 添加列表项到List中
*函数名称：AddMacroListItem
*函数功能：添加列表项到List中
**/
void CInsertWnd::AddMacroListItem(TCHAR *temp)
{
	CListLabelElementUI* pElement=new CListLabelElementUI;
	if (pElement)
	{
		pElement->SetAttribute(_T("height"), _T("30"));
		pElement->SetText(temp);
		m_MacroListUI->Add(pElement);
	}
}

