#include <objbase.h>
#include "UIlib.h"
#include "GlobalVar.h"
#include "MainUI.h"
int WINAPI WinMain(
				   HINSTANCE hInstance,          // handle to the current instance of the application
				   HINSTANCE hPrevInstance,      // handle to the previous instance of the application
				   LPTSTR    lpCmdLine,          // pointer to a null-terminated string that specifies the command line 
				   int       nCmdShow            // specifies how the window is to be shown
				   )
{	
	CPaintManagerUI::SetInstance(hInstance);
	///������Դ·��
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath()+_T("MainUI"));
	///��������ʾ�˻���������
	CMainFrameRobotDlg* pMainDlg =new CMainFrameRobotDlg;
	pMainDlg->Create(NULL, _T("MainFrameRobot"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pMainDlg->CenterWindow();
	::ShowWindow(*pMainDlg,SW_SHOW);
	CPaintManagerUI::MessageLoop();	///<������Ϣѭ��
	::CoUninitialize(); ///<�˳������ͷ�COM��
	return 0;
}

