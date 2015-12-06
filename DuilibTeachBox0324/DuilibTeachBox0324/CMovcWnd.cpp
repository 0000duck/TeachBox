/**
*@file
*文件名称：CMovcWnd.cpp
*
*摘要：Movc指令窗口
*
*@author fly1992@163.com
*
**/
#include "CMovcWnd.h"
#include "CHandleWnd.h"
CMovcWnd::CMovcWnd():m_InstrMovc(INSTRMOVC)
{ 

}
/**
*@brief 设置窗口名称
*函数名称：GetWindowClassName
*函数功能：设置窗口名称
**/
LPCTSTR CMovcWnd::GetWindowClassName() const
{ 
	return _T("UIMovcWnd"); 
}
/**
*@brief 设置窗口类型
*函数名称：GetClassStyle
*函数功能：设置窗口类型
**/
UINT CMovcWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_DIALOG; 
}
/**
*@brief 窗口关闭前最后处理的消息
*函数名称：OnFinalMessage
*函数功能：窗口关闭前最后处理的消息
**/
void CMovcWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}
/**
*@brief 创建窗口之后的初始化工作
*函数名称：Init
*函数功能：创建窗口之后的初始化工作
**/
void CMovcWnd::Init() 
{
	m_pMovcPos=static_cast<CEditUI*>(m_pm.FindControl(_T("MovcP")));
	m_pMovcSpeed=static_cast<CEditUI*>(m_pm.FindControl(_T("MovcV")));
	m_pMovcPL=static_cast<CEditUI*>(m_pm.FindControl(_T("MovcPL")));
	m_pMovcAll=static_cast<CLabelUI*>(m_pm.FindControl(_T("MovcAll")));
}
/**
*@brief 捕获各类窗口消息
*函数名称：Notify
*函数功能：捕获各类窗口消息
**/
void CMovcWnd::Notify(TNotifyUI& msg)
{

	if ( msg.sType == _T("setfocus"))
	{
		if ( msg.pSender->GetName() == _T("MovcP"))
		{
			m_iFlagEdit=0;
			::ShowWindow(KeyPadWnd::GetHandle(m_hWnd)->GetHWND(),SW_SHOW);
		}
		if ( msg.pSender->GetName() == _T("MovcV"))
		{
			m_iFlagEdit=1;
			::ShowWindow(KeyPadWnd::GetHandle(m_hWnd)->GetHWND(),SW_SHOW);
		}
		if ( msg.pSender->GetName() == _T("MovcPL"))
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
LRESULT CMovcWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CControlUI* pRoot=NULL;
	pRoot = builder.Create(INSTRMOVC, (UINT)0, (UINT)0, &m_pm);
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
LRESULT CMovcWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT  CMovcWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return FALSE;
}
/**
*@brief 软键盘消息处理函数
*函数名称：OnInputKeyEdit
*函数功能：软键盘消息处理函数
**/
LRESULT CMovcWnd::OnInputKeyEdit(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CStdString *m_StrEdit=(CStdString*)wParam;
	EditValid *pEditValid=HwndHandle::pEditValid;
	std::string str=Tchar2String(*m_StrEdit);
	switch(m_iFlagEdit)
	{
	case 0:
		if (pEditValid->isValidRobotPos(str))
		{
			m_pMovcPos->SetText(*m_StrEdit);
			m_InstrMovc.SetInstrPos(*m_StrEdit);
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
			m_pMovcSpeed->SetText(*m_StrEdit);
			m_InstrMovc.SetInstrSpeedV(*m_StrEdit);
						HwndHandle::pDisplayTips->DisplayTips(CTips::tipsInfoProduct,VALID_INPUT);
		}
		else
		{
			//MessageBox(NULL,_T("请输入1-100"),_T("提示"),MB_OK);
			HwndHandle::pDisplayTips->DisplayTips(CTips::errorInfoProduct,INVALID_SPEED);
			return FALSE;
		}
		break;
	case 2:
		if (pEditValid->isValidPL(str))
		{
			m_pMovcPL->SetText(*m_StrEdit);
			m_InstrMovc.SetInstrPLV(*m_StrEdit);
			HwndHandle::pDisplayTips->DisplayTips(CTips::tipsInfoProduct,VALID_INPUT);
		}
		else
		{
			//MessageBox(NULL,_T("请输入0-9"),_T("提示"),MB_OK);
			HwndHandle::pDisplayTips->DisplayTips(CTips::errorInfoProduct,INVALID_PL);
			return FALSE;
		}
		break;
	default:
		break;
	}
	m_pMovcAll->SetText(m_InstrMovc.GetInstrAll());
	HwndHandle::stdString=m_InstrMovc.GetInstrDisplay();
	delete m_StrEdit;
	return TRUE;
}
