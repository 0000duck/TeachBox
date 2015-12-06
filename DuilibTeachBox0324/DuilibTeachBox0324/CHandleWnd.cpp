/**
 *@file
 *文件名称：HwndHandle.cpp
 *
 *摘要：包含各个窗口的指针，充当一个中介者，完成各个类之间的信息传递
 *完成初始化动作，窗口指针真正的赋值动作发生在mainUI中
 *
 *@author fly1992@163.com
 *
 **/
#include "CHandleWnd.h"
CStdString HwndHandle::stdString=_T("");
CNewFileWnd* HwndHandle::pNewFileWnd=NULL;
CMainFrameRobotDlg* HwndHandle::pMainFrameRobotDlg=NULL;
CInsertWnd* HwndHandle::pInsertWnd=NULL;
CMovjWnd* HwndHandle::pMovjWnd=NULL;
CMovlWnd* HwndHandle::pMovlWnd=NULL;
CMovcWnd* HwndHandle::pMovcWnd=NULL;
COpenFileWnd* HwndHandle::pOpenFileWnd=NULL;
EditValid *HwndHandle::pEditValid=new EditValid;
CDisplayTips* HwndHandle::pDisplayTips=new CDisplayTips;
CLoginWnd* HwndHandle::pLoginWnd=NULL;
bool  HwndHandle::bParseFlag=0;