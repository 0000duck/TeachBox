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
	///设置资源路径
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath()+_T("MainUI"));
	///创建并显示人机交互窗口
	CMainFrameRobotDlg* pMainDlg =new CMainFrameRobotDlg;
	pMainDlg->Create(NULL, _T("MainFrameRobot"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pMainDlg->CenterWindow();
	::ShowWindow(*pMainDlg,SW_SHOW);
	CPaintManagerUI::MessageLoop();	///<进入消息循环
	::CoUninitialize(); ///<退出程序并释放COM库
	return 0;
}

