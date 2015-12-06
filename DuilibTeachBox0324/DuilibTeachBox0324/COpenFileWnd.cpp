/**
*@file
*文件名称：COpenFileWnd.h
*
*摘要：选择机器人作业文件窗口
*
*@author fly1992@163.com
*
**/
#include "COpenFileWnd.h"

COpenFileWnd::COpenFileWnd()
{ 
	m_iGetItemIndex=0;
}
/**
*@brief 设置窗口名称
*函数名称：GetWindowClassName
*函数功能：设置窗口名称
**/
LPCTSTR COpenFileWnd::GetWindowClassName() const
{ 
	return _T("UIOpenFileFrame"); 
}
/**
*@brief 设置窗口类型
*函数名称：GetClassStyle
*函数功能：设置窗口类型
**/
UINT COpenFileWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_DIALOG;                     
}
/**
*@brief 窗口关闭前最后处理的消息
*函数名称：OnFinalMessage
*函数功能：窗口关闭前最后处理的消息
**/
void COpenFileWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}
/**
*@brief 创建窗口之后的初始化工作
*函数名称：Init
*函数功能：创建窗口之后的初始化工作
**/
void COpenFileWnd::Init() 
{
	m_FileNameList= static_cast<CListUI*>(m_pm.FindControl(_T("DisplayList")));
	//m_NewFileBtn->SetFocus();多于的产物，调了一下午
}
/**
*@brief 捕获各类窗口消息
*函数名称：Notify
*函数功能：捕获各类窗口消息
**/
void COpenFileWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType==_T("itemactivate"))
	{
		m_ListItemText=msg.pSender->GetText();
	}
}
/**
*@brief 加载XML文件，创建窗口
*函数名称：OnCreate
*函数功能：加载XML文件，创建窗口
**/
LRESULT COpenFileWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("DisplayFile.xml"), (UINT)0, (UINT)0, &m_pm);
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
LRESULT COpenFileWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT  COpenFileWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return FALSE;
}
/**
*@brief 往列表中添加一个作业文件
*函数名称：AddFileListItem
*函数功能：往列表中添加一个作业文件
**/
void COpenFileWnd::AddFileListItem(LPCTSTR temp)
{
	CListLabelElementUI* pElement1=new CListLabelElementUI;
	if (pElement1)
	{
		pElement1->SetAttribute(_T("height"), _T("30"));
		pElement1->SetAttribute(_T("textpadding"),_T("5,0,0,0"));
		pElement1->SetText(temp);
		m_FileNameList->Add(pElement1);
	}
}
/**
*@brief 往列表中添加所有作业文件
*函数名称：AddAllFileListItem
*函数功能：往列表中添加所有作业文件
**/
void COpenFileWnd::AddAllFileListItem(std::vector<TSTRING> &vecStr)
{
	m_FileNameList->RemoveAll();
	int i=0;
	CStdString temp=_T("");
	std::vector<TSTRING>::iterator iter=vecStr.begin();
	while(iter!=vecStr.end())
	{
		temp=(*iter).c_str();
		AddFileListItem(temp);
		if (m_ListItemText==((CStdString)_T(" ")+temp))
		{
			m_iGetItemIndex=i;
		}
		i++;
		iter++;//内存不够用 死循环
	}
}
///移除所有作业文件
void COpenFileWnd::RemoveAllListItem()
{
	m_FileNameList->RemoveAll();
}
///获取某一作业文件名称
CStdString COpenFileWnd::GetListItemText(CControlUI* pcontrol)
{
	return m_ListItemText;
}
///选择作业文件，并获取光标
void COpenFileWnd::SelectCurrentListItem()
{
	m_FileNameList->SelectItem(m_iGetItemIndex,true);
}