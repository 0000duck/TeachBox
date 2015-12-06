/**
*@file
*�ļ����ƣ�COpenFileWnd.h
*
*ժҪ��ѡ���������ҵ�ļ�����
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
*@brief ���ô�������
*�������ƣ�GetWindowClassName
*�������ܣ����ô�������
**/
LPCTSTR COpenFileWnd::GetWindowClassName() const
{ 
	return _T("UIOpenFileFrame"); 
}
/**
*@brief ���ô�������
*�������ƣ�GetClassStyle
*�������ܣ����ô�������
**/
UINT COpenFileWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_DIALOG;                     
}
/**
*@brief ���ڹر�ǰ��������Ϣ
*�������ƣ�OnFinalMessage
*�������ܣ����ڹر�ǰ��������Ϣ
**/
void COpenFileWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}
/**
*@brief ��������֮��ĳ�ʼ������
*�������ƣ�Init
*�������ܣ���������֮��ĳ�ʼ������
**/
void COpenFileWnd::Init() 
{
	m_FileNameList= static_cast<CListUI*>(m_pm.FindControl(_T("DisplayList")));
	//m_NewFileBtn->SetFocus();���ڵĲ������һ����
}
/**
*@brief ������ര����Ϣ
*�������ƣ�Notify
*�������ܣ�������ര����Ϣ
**/
void COpenFileWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType==_T("itemactivate"))
	{
		m_ListItemText=msg.pSender->GetText();
	}
}
/**
*@brief ����XML�ļ�����������
*�������ƣ�OnCreate
*�������ܣ�����XML�ļ�����������
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
*@brief windows��Ϣ������
*�������ƣ�HandleMessage
*�������ܣ�windows��Ϣ������
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
*@brief ���б������һ����ҵ�ļ�
*�������ƣ�AddFileListItem
*�������ܣ����б������һ����ҵ�ļ�
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
*@brief ���б������������ҵ�ļ�
*�������ƣ�AddAllFileListItem
*�������ܣ����б������������ҵ�ļ�
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
		iter++;//�ڴ治���� ��ѭ��
	}
}
///�Ƴ�������ҵ�ļ�
void COpenFileWnd::RemoveAllListItem()
{
	m_FileNameList->RemoveAll();
}
///��ȡĳһ��ҵ�ļ�����
CStdString COpenFileWnd::GetListItemText(CControlUI* pcontrol)
{
	return m_ListItemText;
}
///ѡ����ҵ�ļ�������ȡ���
void COpenFileWnd::SelectCurrentListItem()
{
	m_FileNameList->SelectItem(m_iGetItemIndex,true);
}