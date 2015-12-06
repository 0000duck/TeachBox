/**
*@file
*�ļ����ƣ�CFileButtonState.cpp
*
*ժҪ����ҵ�ļ��༭��ť����
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
///��ʼ״̬��������û�а���
buttonState CFileButtonState::Init[]={
	_T(""),FALSE,
	_T(""),FALSE,
	_T(""),FALSE,
	_T(""),FALSE,
	_T(""),FALSE,     
	_T(""),FALSE
};
///����file������״̬
buttonState CFileButtonState::bsInit[]={
	_T("�½�"),TRUE,
	_T(""),FALSE,
	_T(""),FALSE,
	_T(""),FALSE,
	_T(""),FALSE,     
	_T(""),FALSE
};
///��ҵ�༭ʱ��״̬
buttonState CFileButtonState::bsNewOk[]={
	_T("�½�"),FALSE,
	_T("����"),TRUE,
	_T("�޸�"),FALSE,
	_T("ɾ��"),FALSE,
	//_T("SetPC"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///��ҵ�༭ʱ��״̬
buttonState CFileButtonState::bsNewOk1[]={
	_T("�½�"),FALSE,
	_T("����"),TRUE,
	_T("�޸�"),TRUE,
	_T("ɾ��"),TRUE,
	//_T("SetPC"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};

///�������޷�������ҵ�༭ʱ����ť״̬
buttonState CFileButtonState::bsNewOk2[]={//OPERATOR
	_T("�½�"),FALSE,
	_T("����"),FALSE,
	_T("�޸�"),FALSE,
	_T("ɾ��"),FALSE,
	//_T("SetPC"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///�½�֮��ѡ��״̬
buttonState CFileButtonState::bsNew[]={
	_T("ȷ��"),TRUE,
	_T("ȡ��"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///����֮��ѡ��״̬
buttonState CFileButtonState::bsInsert[]={
	_T("ȷ��"),FALSE,
	_T("ȡ��"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};

///ָ�����ѡ��״̬
buttonState CFileButtonState::bsInsertOk[]={
	_T("ȷ��"),TRUE,
	_T("ȡ��"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///�˳�״̬
buttonState CFileButtonState::bsExit[]={
	_T("�˳�"),TRUE,
	_T("����"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///��ҵԤ��״̬
buttonState CFileButtonState::bsInitPro[]={
	_T("��"),TRUE,
	_T("�Ƴ�"),TRUE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};
///��������ҵԤ��״̬
buttonState CFileButtonState::bsInitPro1[]={//OPERATOR
	_T("��"),TRUE,
	_T("�Ƴ�"),FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE,
	_T(""),	  FALSE,
	_T(""),   FALSE
};

/**
*@brief ���ð�ť��ʾ��ʹ��״̬
*�������ƣ�SetFileButtonState
*�������ܣ����ð�ť��ʾ��ʹ��״̬
*param buttonState ��ť״̬�ṹ��ָ��
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
*@brief ��ȡ��ť��ǰ״̬��������һ�ε�״̬
*�������ƣ�ChangeButtonState
*�������ܣ���ȡ��ť��ǰ״̬��������һ�ε�״̬
*param CStdString ��ť�ı�����Ϊʶ���־
**/
void CFileButtonState::ChangeButtonState(CStdString stdStr)
{

	m_oldFlag=m_bflag;
	if (stdStr==_T("�½�"))
	{
		m_bflag=NEW;///<���õ�ǰ״̬Ϊ�½�״̬
	}
	else if (stdStr==_T("����"))
	{
		m_bflag=INSERT;///<���õ�ǰ״̬Ϊ����״̬
	}
	else if(stdStr==_T("ȷ��"))
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
	else if (stdStr==_T("ȡ��"))///<��������½�֮��Ȼ��ȡ��
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
	else if (stdStr==_T("�޸�"))
	{
		m_bflag=MODIFY;
	}
	else if (stdStr==_T("��"))
	{
		m_bflag=OPEN;
	}
	else if (stdStr==_T("�Ƴ�"))
	{
		m_bflag=REMOVEFILE;
	}
	else if (stdStr==_T("ɾ��"))
	{
		m_bflag=DELETEINSTR;
	}
	else if (stdStr==_T("����"))
	{
		m_bflag=BACK;
	}
	else if (stdStr==_T("�˳�"))
	{
		m_bflag=EXIT;
	}
	else {
		return;
	}
	SwitchState(m_bflag);

}
/**
*@brief ���ݰ�ť״̬��־��������Ӧ
*�������ƣ�SwitchState
*�������ܣ���ť״̬��Ӧ
*param ButtonFlag ��ť��־
**/
void CFileButtonState::SwitchState(ButtonFlag bflag)
{
Loop:switch(bflag)
	 {
	case NEW:///<�½���ť���£����ð�ť��״̬
		newRespond();
		break;
	case NEWOK:///<�½���ť����֮��ȷ����ť���£����ð�ť��״̬
		newOkRespond();
		break;
	case NEWCANCLE:///<�½���ť����֮��ȡ����ť���£����ð�ť��״̬
		newCancleRespond();
		break;
	case INSERT:///<���밴��֮�����ð�ť��״̬
		insertRespond();
		break;
	case INSERTCANCLE:///<���밴ť����֮��ȡ����ť���£����ð�ť��״̬
		insertCancleRespond();
		break;
	case INSERTCANCLECANCLE:
		insertCancleCancleRespond();
		break;
	case INSERTOK:///<���밴ť����֮��ȷ����ť���£����ð�ť��״̬
		insertOkRespond();
		break;
	case INSERTOKOK:///<���밴ť����֮��ȷ����ť�����ٴ�ȷ�������ð�ť��״̬
		insertOkOKRespond();
		break;
	case OPEN:///<�򿪰�ť���£����ð�ť��״̬
		openRespond();
		break;
	case DELETEINSTR:///<ɾ����ť����֮�����ð�ť��״̬
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
	case EMPTY:///<һ��ʼ���������£���ʼ״̬����
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
	case EXIT:///<�˳���ť���£����ð�ť��״̬
		exitRespond();
		break;
	case BACK:///<���ذ�ť���£����ð�ť��״̬
		if (m_oldFlag!=BACK)
		{
			bflag=m_oldFlag;///<ȷ����תλ��
			m_bflag=m_oldFlag;///<���õ�ǰ״̬Ϊ������һ�ε�λ��
			goto Loop;
		}
		break;
	 }
}
///�½���ť������Ӧ
void CFileButtonState::newRespond()
{
	SetFileButtonState(bsNew);
	::ShowWindow(HwndHandle::pNewFileWnd->GetHWND(),SW_SHOW);
}
///�½�֮��ȷ����ť������Ӧ
void CFileButtonState::newOkRespond()
{
	CJobDisplay* pjobDiplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
	HwndHandle::stdString=HwndHandle::pNewFileWnd->m_ProgramNameEdit->GetText();
	CStdString strFileName=(CStdString)_T("�ļ�����")+HwndHandle::stdString;
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
///�½�֮��ȡ����ť������Ӧ
void CFileButtonState::newCancleRespond()
{
	SetFileButtonState(bsInit);
	::ShowWindow(HwndHandle::pNewFileWnd->GetHWND(),SW_HIDE);

}
///���밴ť������Ӧ
void CFileButtonState::insertRespond()
{
	SetFileButtonState(bsInsert);
	::ShowWindow(HwndHandle::pInsertWnd->GetHWND(),SW_SHOW);
	::ShowWindow(HwndHandle::pMovjWnd->GetHWND(),SW_HIDE);///<�����Ӵ��ڷ�ֹ�ڸǸ�����
	::ShowWindow(HwndHandle::pMovlWnd->GetHWND(),SW_HIDE);
	::ShowWindow(HwndHandle::pMovcWnd->GetHWND(),SW_HIDE);

}
///����֮��ȷ�ϰ�ť������Ӧ
void CFileButtonState::insertOkRespond()
{
	SetFileButtonState(bsInsertOk);
}
///ָ��ѡ��֮��ȷ�ϰ�ť������Ӧ
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
	HwndHandle::bParseFlag=1;///<�������
	if (pjobDiplay->pRobotJob->jobVector.size()>2)
	{
		SetFileButtonState(bsNewOk1);
	}
	else
	{
		SetFileButtonState(bsNewOk);
	}
	::ShowWindow(HwndHandle::pInsertWnd->GetHWND(),SW_HIDE);///<���ظ����������Ӵ���Ҳ������
}
///����֮��ȡ����ť������Ӧ
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
///ָ��ѡ��֮��ȡ����ť������Ӧ
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
///ɾ����ť������Ӧ
void CFileButtonState::deleteInstrRespond()
{
	CJobDisplay* pjobDiplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
	pjobDiplay->pRobotJob->jobDelete(pjobDiplay->getPc());
	pjobDiplay->pRobotJobData->jobDelete(pjobDiplay->getPc()-1);
	pjobDiplay->pcDown();
	pjobDiplay->jobDisplay();
	pjobDiplay->pcDisplay();

	HwndHandle::bParseFlag=1;///<�������

	if (pjobDiplay->pRobotJob->jobVector.size()>2)
	{
		SetFileButtonState(bsNewOk1);
	}
	else
	{
		SetFileButtonState(bsNewOk);
	}
}
///�ļ��Ƴ���ť������Ӧ
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
///�ļ��򿪰�ť������Ӧ
void CFileButtonState::openRespond()
{
	CListUI* pFileNameList=HwndHandle::pOpenFileWnd->m_FileNameList;
	CJobDisplay* pjobDiplay=HwndHandle::pMainFrameRobotDlg->m_pJobDisplay;
	if (pFileNameList->GetCount()>0)
	{
		int i=pFileNameList->GetCurSel();
		CStdString stdStr=pFileNameList->GetItemAt(i)->GetText();
		CStdString strFileName=(CStdString)_T("�ļ�����")+stdStr;
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
///�ƶ�PCָ����Ӧ
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
///�޸İ�ť������Ӧ
void CFileButtonState::modifyRespond()
{
	ChangeButtonState(_T("����"));
}
///����λ����Ϣ��������
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
///�˳���ť������Ӧ
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