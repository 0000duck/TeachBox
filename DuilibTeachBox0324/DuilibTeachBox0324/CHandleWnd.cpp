/**
 *@file
 *�ļ����ƣ�HwndHandle.cpp
 *
 *ժҪ�������������ڵ�ָ�룬�䵱һ���н��ߣ���ɸ�����֮�����Ϣ����
 *��ɳ�ʼ������������ָ�������ĸ�ֵ����������mainUI��
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