/**
 *@file
 *�ļ����ƣ�HwndHandle.h
 *
 *ժҪ�������������ڵ�ָ�룬�䵱һ���н��ߣ���ɸ�����֮�����Ϣ����
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
///mainui�а���HwndHandle.h Ӧ����mainUI.cpp �ļ��з���ͷ�ļ��������ó���
#include "MainUI.h"
#include "EditValid.h"
#include "LoginWnd.h"
///�����������ڵ�ָ�룬�䵱һ���н��ߣ���ɸ�����֮�����Ϣ����
class HwndHandle
{
public:
	static CDisplayTips* pDisplayTips;///<������Ϣ��ʾָ��
	static EditValid *pEditValid;///<�ַ���Ч���ж���ָ��
	static CNewFileWnd* pNewFileWnd;///<�½�����ָ��
	static CInsertWnd* pInsertWnd;///<���봰��ָ��
	static CMovjWnd* pMovjWnd;///<MOVJ����ָ��
	static CMovlWnd* pMovlWnd;///<MOVL����ָ��
	static CMovcWnd* pMovcWnd;///<MOVC����ָ��
	static CLoginWnd* pLoginWnd;///<��¼����ָ��
	static COpenFileWnd* pOpenFileWnd;///<�ļ�Ԥ������ָ��
	static CMainFrameRobotDlg* pMainFrameRobotDlg;///<������ָ��
	static CStdString stdString;///<����֮��Ҫ���ݵ���Ϣ
	static bool bParseFlag;///<��ҵ�ļ��Ƿ�������
};

