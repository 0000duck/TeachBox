/**
*@file
*�ļ����ƣ�CInsertWnd.cpp
*ժҪ������ָ���
*@author fly1992@163.com
**/
#include "CInsertWnd.h"
#include "CHandleWnd.h"
CInsertWnd::CInsertWnd()
{ 

}
/**
*@brief ���ô�������
*�������ƣ�GetWindowClassName
*�������ܣ����ô�������
**/
LPCTSTR CInsertWnd::GetWindowClassName() const
{ 
	return _T("UIInsertFrame"); 
}
/**
*@brief ���ô�������
*�������ƣ�GetClassStyle
*�������ܣ����ô�������
**/
UINT CInsertWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_DIALOG; 
}
/**
*@brief ���ڹر�ǰ��������Ϣ
*�������ƣ�OnFinalMessage
*�������ܣ����ڹر�ǰ��������Ϣ
**/
void CInsertWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}
/**
*@brief ��������֮��ĳ�ʼ������
*�������ƣ�Init
*�������ܣ���������֮��ĳ�ʼ������
**/
void CInsertWnd::Init() 
{
	m_TreeView=static_cast<CTreeViewUI*>(m_pm.FindControl(_T("RobotTreeView")));
	m_MacroListUI=static_cast<CListUI*>(m_pm.FindControl(_T("Macrolist")));

	HwndHandle::pMovjWnd=new CMovjWnd;///<����MOVJ����
	HwndHandle::pMovjWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0,1,0, 0, 0, NULL);
	::ShowWindow(*HwndHandle::pMovjWnd,SW_HIDE);

	HwndHandle::pMovlWnd=new CMovlWnd;///<����MOVl����
	HwndHandle::pMovlWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0,1,0, 0, 0, NULL);
	::ShowWindow(*HwndHandle::pMovlWnd,SW_HIDE);

	HwndHandle::pMovcWnd=new CMovcWnd;///<����MOVc����
	HwndHandle::pMovcWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0,1,0, 0, 0, NULL);
	::ShowWindow(*HwndHandle::pMovcWnd,SW_HIDE);
}
/**
*@brief ������ര����Ϣ
*�������ƣ�Notify
*�������ܣ�������ര����Ϣ
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
			HwndHandle::pMainFrameRobotDlg->m_pFileButtonState->ChangeButtonState(_T("ȷ��"));
		}
		else if (msg.pSender->GetText()==_T("MOVL"))
		{
			::ShowWindow(*HwndHandle::pMovlWnd,SW_SHOW);
			HwndHandle::pMainFrameRobotDlg->m_pFileButtonState->ChangeButtonState(_T("ȷ��"));
		}
		else if (msg.pSender->GetText()==_T("MOVC"))
		{
			::ShowWindow(*HwndHandle::pMovcWnd,SW_SHOW);
			HwndHandle::pMainFrameRobotDlg->m_pFileButtonState->ChangeButtonState(_T("ȷ��"));
		}
	}
}
/**
*@brief ����XML�ļ�����������
*�������ƣ�OnCreate
*�������ܣ�����XML�ļ�����������
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
*@brief windows��Ϣ������
*�������ƣ�HandleMessage
*�������ܣ�windows��Ϣ������
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
*@brief ����б��List��
*�������ƣ�AddMacroListItem
*�������ܣ�����б��List��
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

