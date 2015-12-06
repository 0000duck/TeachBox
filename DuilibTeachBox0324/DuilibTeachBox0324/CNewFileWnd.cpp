/**
*@file
*�ļ����ƣ�CNewFileWnd.cpp
*
*ժҪ���½���ҵ�ļ�����
*
*@author fly1992@163.com
*
**/
#include "CNewFileWnd.h"
#include "CHandleWnd.h"
CNewFileWnd::CNewFileWnd()
{ 
	m_EditFlag=-1;
}
/**
*@brief ���ô�������
*�������ƣ�GetWindowClassName
*�������ܣ����ô�������
**/
LPCTSTR CNewFileWnd::GetWindowClassName() const
{ 
	return _T("UICNewFileWndFrame"); 
}
/**
*@brief ���ô�������
*�������ƣ�GetClassStyle
*�������ܣ����ô�������
**/
UINT CNewFileWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_DIALOG;                     
}
/**
*@brief ���ڹر�ǰ��������Ϣ
*�������ƣ�OnFinalMessage
*�������ܣ����ڹر�ǰ��������Ϣ
**/
void CNewFileWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}
/**
*@brief ��������֮��ĳ�ʼ������
*�������ƣ�Init
*�������ܣ���������֮��ĳ�ʼ������
**/
void CNewFileWnd::Init() 
{
	m_NewFileBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("NewFileBtn")));
	m_ProgramNameEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("ProgramName")));
	m_ProgramNoteEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("ProgramExpain")));
	//m_NewFileBtn->SetFocus();���ڵĲ������һ����
}
/**
*@brief ������ര����Ϣ
*�������ƣ�Notify
*�������ܣ�������ര����Ϣ
**/
void CNewFileWnd::Notify(TNotifyUI& msg)
{
	if ( msg.sType == _T("setfocus"))
	{
		if ( msg.pSender->GetName() == _T("ProgramName"))
		{
			if( KeyPadWnd::GetHandle(m_hWnd) == NULL ) { Close(); return; }
			::ShowWindow(KeyPadWnd::GetHandle(m_hWnd)->GetHWND(),SW_SHOW);
			m_EditFlag=0;
		}
		else if(msg.pSender->GetName() == _T("ProgramExpain"))
		{
			if( KeyPadWnd::GetHandle(m_hWnd)== NULL ) { Close(); return; }
			::ShowWindow(KeyPadWnd::GetHandle(m_hWnd)->GetHWND(),SW_SHOW);
			m_EditFlag=1;
		}
	}
}
/**
*@brief ����XML�ļ�����������
*�������ƣ�OnCreate
*�������ܣ�����XML�ļ�����������
**/
LRESULT CNewFileWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("NewFile.xml"), (UINT)0, (UINT)0, &m_pm);
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
LRESULT CNewFileWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT CNewFileWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return FALSE;
}
/**
*@brief �������Ϣ������
*�������ƣ�OnInputKeyEdit
*�������ܣ��������Ϣ������
**/
LRESULT CNewFileWnd::OnInputKeyEdit(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CStdString *m_StrEdit=(CStdString*)wParam;
	m_ProgramName=*m_StrEdit;
	 EditValid *pEditValid=HwndHandle::pEditValid;
	 std::string str=Tchar2String(*m_StrEdit);
	switch(m_EditFlag)
	{
	case 0:
		if (pEditValid->isValidFileName(str))
		{
			m_ProgramNameEdit->SetText(*m_StrEdit);
			HwndHandle::pDisplayTips->DisplayTips(CTips::tipsInfoProduct,VALID_INPUT);
		}
		else
		{
			//MessageBox(NULL,_T("������10λ�ַ�/n����ĸ��ͷ"),_T("��ʾ"),MB_OK);
			HwndHandle::pDisplayTips->DisplayTips(CTips::errorInfoProduct,INVALID_FILENAME);
			return FALSE;
		}
		break;
	case 1:
		m_ProgramNoteEdit->SetText(*m_StrEdit);
		break;
	default:
		break;
	}
	delete m_StrEdit;
	return TRUE;
}
