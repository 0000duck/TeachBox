/**
*@file
*文件名称：CFileButtonState.cpp
*
*摘要：作业文件编辑按钮处理
*
*@author fly1992@163.com
*
**/
#include "CFileButtonState.h"   
#include "CHandleWnd.h"
CFileButtonState::
CFileButtonState(FileButtonControl* fbc):m_pfileButtonControl(fbc),
m_bflag(EMPTY),m_bmodifyFlag(0)
{
	SetFileButtonState(Init);
}
///初始状态，物理按键没有按下
buttonState CFileButtonState::Init[]={
	_T(""),FALSE,
	_T(""),FALSE,
	_T(""),FALSE,
	_T(""),FALSE,
	_T(""),FALSE,     
	_T(""),FALSE
};
///按下file按键的状态
buttonState CFileButtonState::bsInit[]={
	_T("新建"),TRUE,
	_T(""),FALSE,
	_T(""),FALSE,
	_T(""),FALSE,
	_T(""),FALSE,     
	_T(""),FALSE
};
///作业编辑时的状态
buttonState CFileButtonState::bsNewOk[]={
	_T("新建"),FALSE,
	_T("插入"),TRUE,
	_T("修改"),FALSE,
	_T("删除"),FALSE,
	//_T("SetPC"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///作业编辑时的状态
buttonState CFileButtonState::bsNewOk1[]={
	_T("新建"),FALSE,
	_T("插入"),TRUE,
	_T("修改"),TRUE,
	_T("删除"),TRUE,
	//_T("SetPC"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};

///操作者无法进行作业编辑时，按钮状态
buttonState CFileButtonState::bsNewOk2[]={//OPERATOR
	_T("新建"),FALSE,
	_T("插入"),FALSE,
	_T("修改"),FALSE,
	_T("删除"),FALSE,
	//_T("SetPC"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///新建之后选择状态
buttonState CFileButtonState::bsNew[]={
	_T("确定"),TRUE,
	_T("取消"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///插入之后选择状态
buttonState CFileButtonState::bsInsert[]={
	_T("确定"),FALSE,
	_T("取消"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};

///指令插入选择状态
buttonState CFileButtonState::bsInsertOk[]={
	_T("确定"),TRUE,
	_T("取消"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///退出状态
buttonState CFileButtonState::bsExit[]={
	_T("退出"),TRUE,
	_T("返回"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///作业预览状态
buttonState CFileButtonState::bsInitPro[]={
	_T("打开"),TRUE,
	_T("移除"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///操作者作业预览状态
buttonState CFileButtonState::bsInitPro1[]={//OPERATOR
	_T("打开"),TRUE,
	_T("移除"),FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};

/**
*@brief 设置按钮显示及使能状态
*函数名称：SetFileButtonState
*函数功能：设置按钮显示及使能状态
*param buttonState 按钮状态结构体指针
**/
void CFileButtonState::SetFileButtonState(buttonState bs[])
{
	m_pfileButtonControl->m_pButtonMenu1->SetText(bs[0].str);
	m_pfileButtonControl->m_pButtonMenu2->SetText(bs[1].str);
	m_pfileButtonControl->m_pButtonMenu3->SetText(bs[2].str);
	m_pfileButtonControl->m_pButtonMenu4->SetText(bs[3].str);
	m_pfileButtonControl->m_pButtonMenu5->SetText(bs[4].str);
	m_pfileButtonControl->m_pButtonMenu6->SetText(bs[5].str);

	m_pfileButtonControl->m_pButtonMenu1->SetEnabled(bs[0].bl);
	m_pfileButtonControl->m_pButtonMenu2->SetEnabled(bs[1].bl);
	m_pfileButtonControl->m_pButtonMenu3->SetEnabled(bs[2].bl);
	m_pfileButtonControl->m_pButtonMenu4->SetEnabled(bs[3].bl);
	m_pfileButtonControl->m_pButtonMenu5->SetEnabled(bs[4].bl);
	m_pfileButtonControl->m_pButtonMenu6->SetEnabled(bs[5].bl);
}
/**
*@brief 获取按钮当前状态并保存上一次的状态
*函数名称：ChangeButtonState
*函数功能：获取按钮当前状态并保存上一次的状态
*param CStdString 按钮文本，作为识别标志
**/
void CFileButtonState::ChangeButtonState(CStdString stdStr)
{

	m_oldFlag=m_bflag;
	if (stdStr==_T("新建"))
	{
		m_bflag=NEW;///<设置当前状态为新建状态
	}
	else if (stdStr==_T("插入"))
	{
		m_bflag=INSERT;///<设置当前状态为插入状态
	}
	else if(stdStr==_T("确定"))
	{
		switch(m_bflag)
		{
		case NEW:
			m_bflag=NEWOK;
			break;
		case INSERT:
			m_bflag=INSERTOK;
			break;
		case INSERTOK:
			m_bflag=INSERTOKOK;
			break;
		default:
			break;
		}
	}
	else if (stdStr==_T("取消"))///<插入或者新建之后，然后取消
	{
		switch(m_bflag)
		{
		case NEW:
			m_bflag=NEWCANCLE;
			break;
		case INSERT:
			m_bflag=INSERTCANCLE;
			break;
		case INSERTOK:
			m_bflag=INSERTCANCLECANCLE;
			break;
		default:
			break;
		}
	}
	else if (stdStr==_T("SetPC"))
	{
		m_bflag=SETPC;
	}
	else if (stdStr==_T("修改"))
	{
		m_bflag=MODIFY;
	}
	else if (stdStr==_T("打开"))
	{
		m_bflag=OPEN;
	}
	else if (stdStr==_T("移除"))
	{
		m_bflag=REMOVEFILE;
	}
	else if (stdStr==_T("删除"))
	{
		m_bflag=DELETEINSTR;
	}
	else if (stdStr==_T("返回"))
	{
		m_bflag=BACK;
	}
	else if (stdStr==_T("退出"))
	{
		m_bflag=EXIT;
	}
	else {
		return;
	}
	SwitchState(m_bflag);

}
/**
*@brief 根据按钮状态标志，作出响应
*函数名称：SwitchState
*函数功能：按钮状态响应
*param ButtonFlag 按钮标志
**/
void CFileButtonState::SwitchState(ButtonFlag bflag)
{
Loop:switch(bflag)
	 {
	case NEW:///<新建按钮按下，设置按钮的状态
		newRespond();
		break;
	case NEWOK:///<新建按钮按下之后确定按钮按下，设置按钮的状态
		newOkRespond();
		break;
	case NEWCANCLE:///<新建按钮按下之后取消按钮按下，设置按钮的状态
		newCancleRespond();
		break;
	case INSERT:///<插入按下之后，设置按钮的状态
		insertRespond();
		break;
	case INSERTCANCLE:///<插入按钮按下之后取消按钮按下，设置按钮的状态
		insertCancleRespond();
		break;
	case INSERTCANCLECANCLE:
		insertCancleCancleRespond();
		break;
	case INSERTOK:///<插入按钮按下之后确定按钮按下，设置按钮的状态
		insertOkRespond();
		break;
	case INSERTOKOK:///<插入按钮按下之后确定按钮按下再次确定，设置按钮的状态
		insertOkOKRespond();
		break;
	case OPEN:///<打开按钮按下，设置按钮的状态
		openRespond();
		break;
	case DELETEINSTR:///<删除按钮按下之后，设置按钮的状态
		deleteInstrRespond();
		break;
	case REMOVEFILE:
		removeFileRespond();
		break;
	case MODIFY:
		m_bmodifyFlag=1;
		modifyRespond();
		break;
	case SETPC:
		setPCRespond();
		break;
	case EMPTY:///<一开始物理按键按下，初始状态设置
		switch(GKW)
		{
		case KEYNEWFILE:
			SetFileButtonState(bsInit);
			break;
		case KEYPROJECT:
			SetFileButtonState(bsInitPro);
			break;
		}
		break;
	case EXIT:///<退出按钮按下，设置按钮的状态
		exitRespond();
		break;
	case BACK:///<返回按钮按下，设置按钮的状态
		if (m_oldFlag!=BACK)
		{
			bflag=m_oldFlag;///<确定跳转位置
			m_bflag=m_oldFlag;///<设置当前状态为返回上一次的位置
			goto Loop;
		}
		break;
	 }
}
///新建按钮按下响应
void CFileButtonState::newRespond()
{
	SetFileButtonState(bsNew);
	::ShowWindow(HwndHandle::pNewFileWnd->GetHWND(),SW_SHOW);
}
///新建之后确定按钮按下响应
void CFileButtonState::newOkRespond()
{
	CJobDisplay* pjobDiplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
	HwndHandle::stdString=HwndHandle::pNewFileWnd->m_ProgramNameEdit->GetText();
	CStdString strFileName=(CStdString)_T("文件名：")+HwndHandle::stdString;
	HwndHandle::pMainFrameRobotDlg->m_pListHeaderItem->SetText(strFileName);
	pjobDiplay->pRobotJob->setJobName(HwndHandle::stdString);
	pjobDiplay->pRobotJobData->setJobName(HwndHandle::stdString);

	pjobDiplay->pRobotJBR->setJobName(HwndHandle::stdString);

	pjobDiplay->setPcZero();
	pjobDiplay->jobDisplay();
	pjobDiplay->pcDisplay();
	if (pjobDiplay->pRobotJob->jobVector.size()>2)
	{
		SetFileButtonState(bsNewOk1);
	}
	else
	{
		SetFileButtonState(bsNewOk);
	}
	::ShowWindow(HwndHandle::pNewFileWnd->GetHWND(),SW_HIDE);
}
///新建之后取消按钮按下响应
void CFileButtonState::newCancleRespond()
{
	SetFileButtonState(bsInit);
	::ShowWindow(HwndHandle::pNewFileWnd->GetHWND(),SW_HIDE);

}
///插入按钮按下响应
void CFileButtonState::insertRespond()
{
	SetFileButtonState(bsInsert);
	::ShowWindow(HwndHandle::pInsertWnd->GetHWND(),SW_SHOW);
	::ShowWindow(HwndHandle::pMovjWnd->GetHWND(),SW_HIDE);///<隐藏子窗口防止遮盖父窗口
	::ShowWindow(HwndHandle::pMovlWnd->GetHWND(),SW_HIDE);
	::ShowWindow(HwndHandle::pMovcWnd->GetHWND(),SW_HIDE);

}
///插入之后确认按钮按下响应
void CFileButtonState::insertOkRespond()
{
	SetFileButtonState(bsInsertOk);
}
///指令选择之后确认按钮按下响应
void CFileButtonState::insertOkOKRespond()
{
	CJobDisplay* pjobDiplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
	std::string strInsert=Tchar2String(HwndHandle::stdString);
	std::string strInsertData=receiceStrAfterInsert(HwndHandle::stdString);
	if (m_bmodifyFlag)
	{
		deleteInstrRespond();
		m_bmodifyFlag=0;
	}
	pjobDiplay->pcUp();
	pjobDiplay->pRobotJob->jobInsert(strInsert,pjobDiplay->getPc());
	pjobDiplay->pRobotJobData->jobInsert(strInsertData,pjobDiplay->getPc()-1);
	pjobDiplay->jobDisplay();
	pjobDiplay->pcDisplay();
	HwndHandle::bParseFlag=1;///<解析标记
	if (pjobDiplay->pRobotJob->jobVector.size()>2)
	{
		SetFileButtonState(bsNewOk1);
	}
	else
	{
		SetFileButtonState(bsNewOk);
	}
	::ShowWindow(HwndHandle::pInsertWnd->GetHWND(),SW_HIDE);///<隐藏父窗口连带子窗口也被隐藏
}
///插入之后取消按钮按下响应
void CFileButtonState::insertCancleRespond()
{
	CJobDisplay* pjobDiplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
	::ShowWindow(HwndHandle::pInsertWnd->GetHWND(),SW_HIDE);
	if (pjobDiplay->pRobotJob->jobVector.size()>2)
	{
		SetFileButtonState(bsNewOk1);
	}
	else
	{
		SetFileButtonState(bsNewOk);
	}
}
///指令选择之后取消按钮按下响应
void CFileButtonState::insertCancleCancleRespond()
{

	CJobDisplay* pjobDiplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
	if (pjobDiplay->pRobotJob->jobVector.size()>2)
	{
		SetFileButtonState(bsNewOk1);
	}
	else
	{
		SetFileButtonState(bsNewOk);
	}
	::ShowWindow(HwndHandle::pInsertWnd->GetHWND(),SW_HIDE);
}
///删除按钮按下响应
void CFileButtonState::deleteInstrRespond()
{
	CJobDisplay* pjobDiplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
	pjobDiplay->pRobotJob->jobDelete(pjobDiplay->getPc());
	pjobDiplay->pRobotJobData->jobDelete(pjobDiplay->getPc()-1);
	pjobDiplay->pcDown();
	pjobDiplay->jobDisplay();
	pjobDiplay->pcDisplay();

	HwndHandle::bParseFlag=1;///<解析标记

	if (pjobDiplay->pRobotJob->jobVector.size()>2)
	{
		SetFileButtonState(bsNewOk1);
	}
	else
	{
		SetFileButtonState(bsNewOk);
	}
}
///文件移除按钮按下响应
void CFileButtonState::removeFileRespond()
{
	CListUI* pFileNameList=HwndHandle::pOpenFileWnd->m_FileNameList;
	if (pFileNameList->GetCount()>0)
	{
		int i=pFileNameList->GetCurSel();
		CStdString stdStr=pFileNameList->GetItemAt(i)->GetText();
		CJobDisplay *pJobDisplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
		pJobDisplay->pRobotJob->jobFileDelete(stdStr);
		pJobDisplay->pRobotJobData->jobFileDelete(stdStr);
		pJobDisplay->pRobotJBR->jobFileDelete(stdStr);

		pJobDisplay->pRobotJBR->deleteJBRFile(Tchar2String(stdStr));

		std::vector<TSTRING> vec=pJobDisplay->pRobotJob->getJobFileNameVector();
		HwndHandle::pOpenFileWnd->AddAllFileListItem(vec);
		::ShowWindow(HwndHandle::pOpenFileWnd->GetHWND(),SW_SHOW);
	}
}
///文件打开按钮按下响应
void CFileButtonState::openRespond()
{
	CListUI* pFileNameList=HwndHandle::pOpenFileWnd->m_FileNameList;
	CJobDisplay* pjobDiplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
	if (pFileNameList->GetCount()>0)
	{
		int i=pFileNameList->GetCurSel();
		CStdString stdStr=pFileNameList->GetItemAt(i)->GetText();
		CStdString strFileName=(CStdString)_T("文件名：")+stdStr;
		HwndHandle::pMainFrameRobotDlg->m_pListHeaderItem->SetText(strFileName);
		pjobDiplay->pRobotJob->readJob(stdStr);
		pjobDiplay->pRobotJobData->readJob(stdStr);

		pjobDiplay->pRobotJBR->readJob(stdStr);

		pjobDiplay->setPcZero();
		pjobDiplay->jobDisplay();
		pjobDiplay->pcDisplay();
		if(USLM==OPERATOR)
		{
			SetFileButtonState(bsNewOk2);//operator
		}
		else{

			if (pjobDiplay->pRobotJob->jobVector.size()>2)
			{
				SetFileButtonState(bsNewOk1);
			}
			else
			{
				SetFileButtonState(bsNewOk);
			}
		}

		::ShowWindow(HwndHandle::pOpenFileWnd->GetHWND(),SW_HIDE);
	}
	
	::ShowWindow(HwndHandle::pNewFileWnd->GetHWND(),SW_HIDE);
}
///移动PC指针响应
void CFileButtonState::setPCRespond()
{
	CJobDisplay* pjobDiplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
	pjobDiplay->pcUp();
	if (pjobDiplay->getPc()==pjobDiplay->pRobotJob->jobVector.size()-1)
	{
		pjobDiplay->pcDisplay();
		pjobDiplay->pcUp();
	}
	pjobDiplay->pcDisplay();
}
///修改按钮按下响应
void CFileButtonState::modifyRespond()
{
	ChangeButtonState(_T("插入"));
}
///接受位置信息，并保存
std::string CFileButtonState::receiceStrAfterInsert(CStdString stdStr)
{
	std::string str=Tchar2String(stdStr);
	std::string strInstr;
	CInstrControl* pInstrControl=HwndHandle::pMainFrameRobotDlg->m_pRobot->m_pInstrControl;
	
	if (str.substr(0,4)=="MOVJ")
	{
		pInstrControl->sendInstrControlInstr(INSERTMOVJ);
	}
	else if (str.substr(0,4)=="MOVL")
	{
		pInstrControl->sendInstrControlInstr(INSERTMOVL);
	}
	else if (str.substr(0,4)=="MOVC")
	{
		pInstrControl->sendInstrControlInstr(INSERTMOVC);
	}
	strInstr=str.substr(5,4);//P000
	Delayms(20);
	std::string strReceive=pInstrControl->receiveControlInstr();

	int ibegin=0;
	ibegin=strReceive.find(' ',ibegin);
	while(ibegin!=-1)
	{
		strReceive.replace(ibegin,1,1,',');
		ibegin=strReceive.find(' ',ibegin);
	}
	strInstr=strInstr+"="+strReceive;
	return strInstr;
}
///退出按钮按下响应
void CFileButtonState::exitRespond()
{
	switch(GKW)
	{
	case KEYNEWFILE:
		SetFileButtonState(bsInit);
		break;
	case KEYPROJECT:
		CListUI* pFileNameList=HwndHandle::pOpenFileWnd->m_FileNameList;
		if (pFileNameList->GetCount()>0)
		{
			pFileNameList->SelectItem(0);
		}
		CJobInterface *pRobotJob=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay->pRobotJob;
		std::vector<TSTRING> vec=pRobotJob->getJobFileNameVector();
		HwndHandle::pOpenFileWnd->AddAllFileListItem(vec);
		::ShowWindow(HwndHandle::pOpenFileWnd->GetHWND(),SW_SHOW);
		if(USLM==OPERATOR)
		{
			SetFileButtonState(bsInitPro1);
		}
		else{
			SetFileButtonState(bsInitPro);
		}
		break;
	}
}