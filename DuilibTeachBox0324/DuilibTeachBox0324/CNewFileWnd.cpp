/**
*@file
*文件名称：CNewFileWnd.cpp
*
*摘要：新建作业文件窗口
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
*@brief 设置窗口名称
*函数名称：GetWindowClassName
*函数功能：设置窗口名称
**/
LPCTSTR CNewFileWnd::GetWindowClassName() const
{ 
	return _T("UICNewFileWndFrame"); 
}
/**
*@brief 设置窗口类型
*函数名称：GetClassStyle
*函数功能：设置窗口类型
**/
UINT CNewFileWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_DIALOG;                     
}
/**
*@brief 窗口关闭前最后处理的消息
*函数名称：OnFinalMessage
*函数功能：窗口关闭前最后处理的消息
**/
void CNewFileWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}
/**
*@brief 创建窗口之后的初始化工作
*函数名称：Init
*函数功能：创建窗口之后的初始化工作
**/
void CNewFileWnd::Init() 
{
	m_NewFileBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("NewFileBtn")));
	m_ProgramNameEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("ProgramName")));
	m_ProgramNoteEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("ProgramExpain")));
	//m_NewFileBtn->SetFocus();多于的产物，调了一下午
}
/**
*@brief 捕获各类窗口消息
*函数名称：Notify
*函数功能：捕获各类窗口消息
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
*@brief 加载XML文件，创建窗口
*函数名称：OnCreate
*函数功能：加载XML文件，创建窗口
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
*@brief windows消息处理函数
*函数名称：HandleMessage
*函数功能：windows消息处理函数
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
*@brief 软键盘消息处理函数
*函数名称：OnInputKeyEdit
*函数功能：软键盘消息处理函数
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
			//MessageBox(NULL,_T("请输入10位字符/n以字母开头"),_T("提示"),MB_OK);
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
