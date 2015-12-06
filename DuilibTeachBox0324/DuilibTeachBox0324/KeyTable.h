#pragma once
#include "GlobalVar.h"
//////////////////////////////////////////////////////////////////////////
class KeyPadUI : public CContainerUI
{
public:
	KeyPadUI()
	{
		CDialogBuilder builder;
		CContainerUI* pKeyPadUI = static_cast<CContainerUI*>(builder.Create(_T("KeyPad.xml"), (UINT)0));
		if( pKeyPadUI ) 
		{
			this->Add(pKeyPadUI);
		}
		else 
		{
			this->RemoveAll();
			return;
		}
	}
};
////////////////////////////////////////////////////////////////////////////
class CDialogBuilderCallbackEx : public IDialogBuilderCallback
{
public:
	CControlUI* CreateControl(LPCTSTR pstrClass) 
	{
		if( _tcscmp(pstrClass, _T("KeyPad")) == 0 ) return new KeyPadUI;
		return NULL;
	}
};
//////////////////////////////////////////////////////////////////////////
