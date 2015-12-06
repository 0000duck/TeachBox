/**
 *@file
 *文件名称：HwndHandle.h
 *
 *摘要：包含各个窗口的指针，充当一个中介者，完成各个类之间的信息传递
 *
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CNewFileWnd.h"
#include "CInsertWnd.h"
#include "CMovjWnd.h"
#include "CMovlWnd.h"
#include "CMovcWnd.h"
#include "COpenFileWnd.h"
///mainui中包含HwndHandle.h 应放在mainUI.cpp 文件中否则头文件交叉引用出错
#include "MainUI.h"
#include "EditValid.h"
#include "LoginWnd.h"
///包含各个窗口的指针，充当一个中介者，完成各个类之间的信息传递
class HwndHandle
{
public:
	static CDisplayTips* pDisplayTips;///<错误信息提示指针
	static EditValid *pEditValid;///<字符有效性判断类指针
	static CNewFileWnd* pNewFileWnd;///<新建窗口指针
	static CInsertWnd* pInsertWnd;///<插入窗口指针
	static CMovjWnd* pMovjWnd;///<MOVJ窗口指针
	static CMovlWnd* pMovlWnd;///<MOVL窗口指针
	static CMovcWnd* pMovcWnd;///<MOVC窗口指针
	static CLoginWnd* pLoginWnd;///<登录窗口指针
	static COpenFileWnd* pOpenFileWnd;///<文件预览串口指针
	static CMainFrameRobotDlg* pMainFrameRobotDlg;///<主窗口指针
	static CStdString stdString;///<窗口之间要传递的信息
	static bool bParseFlag;///<作业文件是否解析标记
};

