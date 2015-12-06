#include "MainUI.h"
#include "CHandleWnd.h"
/**
 *@brief ���캯��
 *�������ƣ�CMainFrameRobotDlg
 *�������ܣ����캯��
 **/
CMainFrameRobotDlg::CMainFrameRobotDlg(void)
{
	m_pFileButtonControl=new FileButtonControl;
	m_pStateControl=new StateControl;
	m_pCoordControl=new CoordControl;
	m_pRobot=new CRobot;
	
	KeyPadWnd* keyPadWnd=KeyPadWnd::GetHandle(NULL);///<���������
	keyPadWnd->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, 0, 0, 0, 0, 0, NULL);
}

CMainFrameRobotDlg::~CMainFrameRobotDlg(void)
{

}
/**
*@brief ���ô�������
*�������ƣ�GetWindowClassName
*�������ܣ����ô�������
**/
LPCTSTR CMainFrameRobotDlg::GetWindowClassName() const
{
	return _T("MainFrameRobot");
}
/**
*@brief windows��Ϣ������
*�������ƣ�HandleMessage
*�������ܣ�windows��Ϣ������
**/
LRESULT CMainFrameRobotDlg::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	switch( uMsg ) 
	{
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled);	break;
	case WM_CLOSE:		   lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}

	if( bHandled ) return lRes;
	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;

	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}
/**
*@brief ����XML�ļ�����������
*�������ƣ�OnCreate
*�������ܣ�����XML�ļ�����������
**/
LRESULT CMainFrameRobotDlg::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	m_PaintManager.Init(m_hWnd);
	m_PaintManager.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("MainUI.xml"), (UINT)0, NULL, &m_PaintManager);   // DemoSkin.xml��Ҫ�ŵ�exeĿ¼��
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);   ///< ��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����
	Init();
	return 0;
}

LRESULT CMainFrameRobotDlg::OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{

	bHandled = FALSE;
	return 0;
}

LRESULT CMainFrameRobotDlg::OnDestroy( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{

	::PostQuitMessage(0L);
	bHandled = FALSE;
	return 0;
}
/**
 *@brief ���ֿؼ�֪ͨ��Ϣ������
 *�������ƣ�Notify
 *�������ܣ����ֿؼ�֪ͨ��Ϣ������
 **/
void CMainFrameRobotDlg::Notify( TNotifyUI& msg )
{
	if( msg.sType == _T("windowinit") ) 
	{
		OnWindowInit();
	}
	else if( msg.sType == _T("click") ) {

		OnLBtnClick(msg.pSender);
	}
}  
/**
 *@brief ��ʼ������ʾ���ļ��༭����
 *�������ƣ�InitFileButtonControl
 *�������ܣ���ʼ������ʾ���ļ��༭���������½������룬ɾ����setPC��
 **/
void CMainFrameRobotDlg::InitFileButtonControl()
{
	m_pFileButtonControl->m_pButtonMenu1 = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonMenu1")));
	m_pFileButtonControl->m_pButtonMenu2 = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonMenu2")));
	m_pFileButtonControl->m_pButtonMenu3 = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonMenu3")));
	m_pFileButtonControl->m_pButtonMenu4 = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonMenu4")));	
	m_pFileButtonControl->m_pButtonMenu5 = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonMenu5")));
	m_pFileButtonControl->m_pButtonMenu6 = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonMenu6")));
	m_pFileButtonControl->m_pButtonReturn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("ButtonReturn")));
	m_pFileButtonState=new CFileButtonState(m_pFileButtonControl);
}

/**
 *@brief ��ʼ������״̬�ؼ�
 *�������ƣ�InitStateControl
 *�������ܣ���ʼ������״̬�ؼ�����ö�Ӧ��ָ�룬���ŷ�״̬��
 **/
void CMainFrameRobotDlg::InitStateControl()
{
	m_pStateControl->m_pRobotDriverIcon = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("RobotDriver")));
	m_pStateControl->m_pRobotDriverText=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("RobotDriverText")));

	m_pStateControl->m_pRobotModelIcon = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("RobotModel")));
	m_pStateControl->m_pRobotModelText=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("RobotModelText")));

	m_pStateControl->m_pRobotExecuIcon = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("RobotRunState")));
	m_pStateControl->m_pRobotExecuText=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("RobotRunStateText")));

	m_pStateControl->m_pRobotSpeedIcon = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("RobotSpeed")));
	m_pStateControl->m_pRobotSpeedText=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("RobotSpeedText")));

	m_pStateControl->m_pRobotCoordIcon = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("RobotCoord")));
	m_pStateControl->m_pRobotCoordText=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("RobotCoordText")));

	m_pStateControl->m_pRobotSyncIcon = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("SynchronizedRobot")));
	m_pStateControl->m_pRobotSyncText=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("SynchronizedRobotText")));

	
	m_pStateControl->m_pRobotObjIcon = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("ControlAxis")));
	m_pStateControl->m_pRobotObjText=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("ControlAxisText")));

}

/**
 *@brief ����ؼ��ĳ�ʼ������
 *�������ƣ�InitCoordControl
 *�������ܣ�����ؼ��ĳ�ʼ����������ʼ�����ᣬͬ��ģʽ�£�Ӧ���ܹ���ҳ
 **/
void CMainFrameRobotDlg::InitCoordControl()
{
	m_pCoordControl->m_pRobotAxis1=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("Axis1Text")));
	m_pCoordControl->m_pRobotAxis2=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("Axis2Text")));
	m_pCoordControl->m_pRobotAxis3=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("Axis3Text")));
	m_pCoordControl->m_pRobotAxis4=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("Axis4Text")));
	m_pCoordControl->m_pRobotAxis5=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("Axis5Text")));
	m_pCoordControl->m_pRobotAxis6=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("Axis6Text")));
	m_pCoordControl->m_pRobotAxis7=static_cast<CControlUI*>(m_PaintManager.FindControl(_T("Axis7Text")));
}
/**
 *@brief ��ɸ��ӿؼ��ĳ�ʼ������
 *�������ƣ�InitComplicateControl
 *�������ܣ���ɸ��ӿؼ��ĳ�ʼ������������Ͽ��б�ȣ������Ӧ��ָ��
 **/
void CMainFrameRobotDlg::InitComplicateControl()
{
	m_pComboError= static_cast<CComboUI*>(m_PaintManager.FindControl(_T("ComboErrorInfo")));
	m_pListHeaderItem=static_cast<CListHeaderItemUI*>(m_PaintManager.FindControl(_T("MainFileName")));
	m_pRobotList = static_cast<CListUIEx*>(m_PaintManager.FindControl(_T("domainlist")));
	CTips::GetInstance(m_pComboError);
	m_pJobDisplay=new CJobDisplay(m_pRobotList);
}
/**
 *@brief �����������ֿؼ��ĳ�ʼ������
 *�������ƣ�Init
 *�������ܣ������������ֿؼ��ĳ�ʼ�������������Ӧ��ָ��
 **/
void CMainFrameRobotDlg::Init()
{
	InitFileButtonControl();
	InitStateControl();
	InitCoordControl();
	CMainFrameRobotDlg::InitComplicateControl();
	TECH_BOX_ERR_CODE TEACHINIT=TechBoxLibInit(this->m_hWnd,WM_TECHBOX_KEY_CHANGE,WM_TECHBOX_MPG);

	HwndHandle::pNewFileWnd=new CNewFileWnd;///<�����½�����
	HwndHandle::pNewFileWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0, 1,86, 0, 0, NULL);
	::ShowWindow(*HwndHandle::pNewFileWnd,SW_HIDE);

	HwndHandle::pInsertWnd=new CInsertWnd;///<�������봰��
	HwndHandle::pInsertWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0, 1,86, 0, 0, NULL);
	::ShowWindow(*HwndHandle::pInsertWnd,SW_HIDE);

	HwndHandle::pOpenFileWnd=new COpenFileWnd;///<�������봰��
	HwndHandle::pOpenFileWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0,1,86 , 0, 0, NULL);
	::ShowWindow(*HwndHandle::pOpenFileWnd,SW_HIDE);


	HwndHandle::pMainFrameRobotDlg=this;///<���������ھ��

	HWND hWnd=::FindWindow(_T("HHTaskBar"),NULL);
	::ShowWindow(hWnd,SW_HIDE);///<����������
}

void CMainFrameRobotDlg::OnWindowInit()
{
	HwndHandle::pLoginWnd=new CLoginWnd;///<�������봰��
	HwndHandle::pLoginWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0, 0, 0, 0, 0, NULL);
	HwndHandle::pLoginWnd->ShowModal();
}
/**
 *@brief ���ʾ���ļ��༭��ť����Ӧ
 *�������ƣ�OnLBtnClick
 *�������ܣ����ʾ���ļ��༭��ť����Ӧ
 **/
void CMainFrameRobotDlg::OnLBtnClick(CControlUI *pControl)
{

	m_pFileButtonState->ChangeButtonState(pControl->GetText());
   if (pControl->GetName()==_T("ButtonMenu6"))
	{
		PostQuitMessage(0);
	}
	else if (pControl->GetName()==_T("ButtonReturn"))
	{
		if (m_pRobot->m_pSync->GetState()==CRobotStateValue::SYNC)
		{
			if (m_pRobot->m_pCoord->GetState()==CRobotStateValue::COORDJOINT)
			{
				m_pRobot->m_pCoord->PosAndJointCoordSwitch();
			}
			else
			{
				m_pRobot->m_pServe->DisplayTips(CTips::errorInfoProduct,PLEASE_SWITCH_JOINT_COORD);	
				CDisplayDevManager::displayLed->On(CDisplayDevManager::LEDERROR);
			}
		}
		else 
		{
			m_pRobot->m_pServe->DisplayTips(CTips::errorInfoProduct,NOT_SYNC_MODEL);
			CDisplayDevManager::displayLed->On(CDisplayDevManager::LEDERROR);
		}
	}
}
/**
 *@brief �˴���Ҫ��������Ϣ��Ӧ
 *�������ƣ�MessageHandler
 *�������ܣ��˴���Ҫ��������Ϣ��Ӧ
 *@return LRESULT ������
 **/
LRESULT  CMainFrameRobotDlg::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (uMsg==WM_TECHBOX_KEY_CHANGE)
	{
		TeachBoxKeyHandle* teachBoxHandle=TeachBoxKeyHandle::GetHandle(this);
		teachBoxHandle->KeyMessageHandle(wParam);	
	}
	return TRUE;
}
///�����������൥��ģʽָ�����
TeachBoxKeyHandle* TeachBoxKeyHandle::teachBoxHandle=NULL;
///�����������๹�캯��
TeachBoxKeyHandle::TeachBoxKeyHandle(CMainFrameRobotDlg* pMain):m_pMainUI(pMain)
{
	for (int i=0;i<KEYNUMBER;i++)
	{
		KeyHandle[i]=NULL;
	}
	CreateMapKeyHandle();///<������������Ӧӳ���ϵ
	m_pMainUI->m_pRobot->m_pCoord->SetCoordControl(m_pMainUI->m_pCoordControl);
	///<�������ø����������־
	m_bflag1=1;
	m_bflag2=1;
	m_bKeyUpFlag=0;
	m_bShutDow=0;

}
/**
 *@brief ��ȡ�����������൥��ģʽָ�����
 *�������ƣ�GetHandle
 *�������ܣ���ȡ�����������൥��ģʽָ�����
 * @param CMainFrameRobotDlg* �Ի���ָ��
 * @return �����������൥��ģʽָ�����
 **/
TeachBoxKeyHandle* TeachBoxKeyHandle::GetHandle(CMainFrameRobotDlg* pMain)
{
	if (teachBoxHandle==NULL)
	{
		teachBoxHandle=new TeachBoxKeyHandle(pMain);
	}
	return teachBoxHandle;
}
/**
 *@brief �����ŷ�״̬
 *�������ƣ�ServeHandle
 *�������ܣ������ŷ�״̬
 **/
void TeachBoxKeyHandle::ServeHandle(void*)
{
	m_pMainUI->m_pRobot->DisplayState(CRobot::m_pServe,
		m_pMainUI->m_pStateControl->m_pRobotDriverText,
		m_pMainUI->m_pStateControl->m_pRobotDriverIcon);
	static bool bflag=1;
	if (bflag)
	{
		Delayms(20);
		CoordHandle(NULL);///<��Ϊ�û�����
		bflag=0;
	}
	
}
/**
 *@brief ʾ���ٶ����� 
 *�������ƣ�SpeedHandle
 *�������ܣ�ʾ���ٶ�����
 **/
void TeachBoxKeyHandle::SpeedHandle(void*)
{
	m_pMainUI->m_pRobot->DisplayState(CRobot::m_pSpeed,
		m_pMainUI->m_pStateControl->m_pRobotSpeedText,
		m_pMainUI->m_pStateControl->m_pRobotSpeedIcon);
}
/**
 *@brief ������������
 *�������ƣ�CoordHandle
 *�������ܣ�������������
 **/
void TeachBoxKeyHandle::CoordHandle(void*)
{
	m_pMainUI->m_pRobot->DisplayState(CRobot::m_pCoord,
		m_pMainUI->m_pStateControl->m_pRobotCoordText,
		m_pMainUI->m_pStateControl->m_pRobotCoordIcon);
}
/**
 *@brief ͬ��ģʽ����
 *�������ƣ�SyncHandle
 *�������ܣ�ͬ��ģʽ����
 **/
void TeachBoxKeyHandle::SyncHandle(void*)
{
	m_pMainUI->m_pRobot->DisplayState(CRobot::m_pSync,
		m_pMainUI->m_pStateControl->m_pRobotSyncText,
		m_pMainUI->m_pStateControl->m_pRobotSyncIcon);
}

/**
 *@brief ������ģʽ����
 *�������ƣ�ModelHandle
 *�������ܣ�������ģʽ����
 **/
void TeachBoxKeyHandle::ModelHandle(void*)
{
	m_pMainUI->m_pRobot->DisplayState(CRobot::m_pModel,
		m_pMainUI->m_pStateControl->m_pRobotModelText,
		m_pMainUI->m_pStateControl->m_pRobotModelIcon);
	int iState=m_pMainUI->m_pRobot->m_pModel->GetState();
	if (iState==CRobotStateValue::MODELTEACH)
	{
		while (m_pMainUI->m_pJobDisplay->getPc())
		{
			m_pMainUI->m_pFileButtonState->setPCRespond();
		}
	}
}
/**
 *@brief ���������ְ�ť����
 *�������ƣ�StartHandle
 *�������ܣ����������ְ�ť����
 **/
void TeachBoxKeyHandle::StartHandle(void*)
{

	int iState=m_pMainUI->m_pRobot->m_pModel->GetState();
	CRobotJBR* pRobotJBR=m_pMainUI->m_pJobDisplay->pRobotJBR;
	std::vector<std::string> vecJob=pRobotJBR->jobVector;
	if (HwndHandle::bParseFlag)
	{
		pRobotJBR->generateFiles();
		HwndHandle::bParseFlag=0;
	}
	if (iState==CRobotStateValue::MODELREPALY)
	{
		for (int i=0;i<vecJob.size();i++)
		{
			m_pMainUI->m_pRobot->m_pJobControl->sendJobControlInstr(vecJob[i]);
			Delayms(10);
		}
		m_pMainUI->m_pRobot->m_pInstrControl->sendInstrControlInstr(INSTREND);
	}
}
/**
 *@brief ������ʾ�̰�ť����
 *�������ƣ�StepHandle
 *�������ܣ��ǻ�����ʾ�̰�ť����
 **/
void TeachBoxKeyHandle::StepHandle(void*)
{
	CRobotJBR* pRobotJBR=m_pMainUI->m_pJobDisplay->pRobotJBR;
	int iState=m_pMainUI->m_pRobot->m_pModel->GetState();
	if (iState==CRobotStateValue::MODELREPALY)
		return;
	
	int i=m_pMainUI->m_pJobDisplay->getPc();
	if (HwndHandle::bParseFlag)
	{

		pRobotJBR->generateFiles();
		pRobotJBR->readJob(pRobotJBR->getJobName());
		HwndHandle::bParseFlag=0;

	}

	std::vector<std::string> vecJob=m_pMainUI->m_pJobDisplay->pRobotJob->jobVector;
	std::vector<std::string> vecJobData=pRobotJBR->jobVector;
	if (i<vecJobData.size())
	{
		if (vecJob[i+1].substr(0,4)=="MOVJ"||vecJob[i+1].substr(0,4)=="MOVL")
		{
			
			m_pMainUI->m_pRobot->m_pJobControl->sendJobControlInstr(vecJobData[i]);
			Delayms(10);
			m_pMainUI->m_pFileButtonState->setPCRespond();
			m_pMainUI->m_pRobot->m_pInstrControl->sendInstrControlInstr(INSTREND);
		}
		else if (vecJob[i+1].substr(0,4)=="MOVC")
		{
			for (int j=0;j<3;j++)
			{
				m_pMainUI->m_pRobot->m_pJobControl->sendJobControlInstr(vecJobData[i]);
				Delayms(10);
				m_pMainUI->m_pFileButtonState->setPCRespond();
			}	
			m_pMainUI->m_pRobot->m_pInstrControl->sendInstrControlInstr(INSTREND);
		}
		return;
	}
	m_pMainUI->m_pFileButtonState->setPCRespond();

}
/**
 *@brief ���û����˶���
 *�������ƣ�RobotObjHandle
 *�������ܣ����û����˶���
 **/
void TeachBoxKeyHandle::RobotObjHandle(void*)
{
	m_pMainUI->m_pRobot->DisplayState(CRobot::m_pRobotObj,
		m_pMainUI->m_pStateControl->m_pRobotObjText,
		m_pMainUI->m_pStateControl->m_pRobotObjIcon);
}
/**
 *@brief �����������Ͷ�Ӧ��Ӧ����֮���ӳ��
 *�������ƣ�CreateMapKeyHandle
 *�������ܣ������������Ͷ�Ӧ��Ӧ����֮���ӳ��
 **/
void TeachBoxKeyHandle::CreateMapKeyHandle(void)
{
	int ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYSERVE);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::ServeHandle;///<ָ��������TeachBoxKeyHandle
	
	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYSPEED);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::SpeedHandle;///<ָ��������TeachBoxKeyHandle

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYCOORD);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::CoordHandle;///<ָ��������TeachBoxKeyHandle

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYROBOT);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::RobotObjHandle;///<ָ��������TeachBoxKeyHandle

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYSYNC);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::SyncHandle;///<ָ��������TeachBoxKeyHandle

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYCONNECT);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::TcpConnect;

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYNEWFILE);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::NewFileHandle;

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYPROJECT);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::ProjectHandle;

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYMODEL);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::ModelHandle;

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYSTART);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::StartHandle;

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYSTEP);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::StepHandle;

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYSHUTDOWN1);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::ShutDownHandle1;

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYSHUTDOWN2);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::ShutDownHandle2;
	///������Ҫ������Ӻ�����Ӧӳ��,���Ըĳ�map���򻯴���
	for (int i=0,j=CTeachBoxKeyValue::KEYAXISSM;i<NUMAXISCONTROL;i++)
	{
		ikeyIndex=GetTeachBoxKeyIndex(j);
		j=j<<1;
		KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::AxisControlHandle;
	}
}
/**
 *@brief ��������Ӧ����
 *�������ƣ�KeyMessageHandle
 *�������ܣ���������Ӧ����
 * @param ikeyValue ��������ֵ 
 **/
void TeachBoxKeyHandle::KeyMessageHandle(int ikeyValue)
{

	int keyIndex=GetTeachBoxKeyIndex(ikeyValue);
	if (ikeyValue!=CTeachBoxKeyValue::KEYSERVE)
		if(ikeyValue!=CTeachBoxKeyValue::KEYCONNECT)
			if (ikeyValue!=CTeachBoxKeyValue::KEYSHUTDOWN1)
				if (ikeyValue!=CTeachBoxKeyValue::KEYSHUTDOWN2)
						if(m_pMainUI->m_pRobot->m_pServe->GetState()==CRobotStateValue::SERVEOFF)
						
	{
		///��Ӵ�����ʾ
		return ;
	}
	if (USLM==OPERATOR)
	{
		switch(ikeyValue)
		{
			case CTeachBoxKeyValue::KEYSERVE:
			case CTeachBoxKeyValue::KEYPROJECT:
			case CTeachBoxKeyValue::KEYCONNECT:
			case CTeachBoxKeyValue::KEYMODEL:
			case CTeachBoxKeyValue::KEYSTART:
			case CTeachBoxKeyValue::KEYSTEP:
			case CTeachBoxKeyValue::KEYSHUTDOWN1:
			case CTeachBoxKeyValue::KEYSHUTDOWN2:
				break;
			default:
				return;
				break;
		}
	}
	if (ikeyValue==CTeachBoxKeyValue::KEYUP)///<��������ʱ�����Ӧ
	{
		if (m_bKeyUpFlag)
		{
			m_pMainUI->m_pRobot->m_pAxisControl->sendAxisControlInstr(AXISSTOP);
			m_bKeyUpFlag=0;
		}
		return;
	}
	if (keyIndex>=9&&keyIndex<=20)//���������Ӧ
	{
		int num=keyIndex-9;
		(this->*KeyHandle[keyIndex])((void*)&num);
	}
	else if(KeyHandle[keyIndex])
	{
		(this->*KeyHandle[keyIndex])(NULL);///<һ��Ҫ���thisָ�룬���Ҽ�*��
	}	
}

/**
 *@brief ��ȡ��������Ӧ�����ں���ָ�������е�����
 *�������ƣ�GetTeachBoxKeyIndex
 *�������ܣ���ȡ��������Ӧ�����ں���ָ�������е�����
 * @param keyValue �������ļ�ֵ
 * @return index ����ֵ 
 **/
int TeachBoxKeyHandle::GetTeachBoxKeyIndex(int keyValue)
{
	int index=0;
	while (keyValue)
	{
		keyValue=keyValue>>1;
		index++;
	}
	return index-1;
}
/**
 *@brief ����TCPIPͨ������
 *�������ƣ�TcpConnect
 *�������ܣ�����TCPIPͨ������
 **/
void TeachBoxKeyHandle::TcpConnect(void*)
{
	CTCPClient_CE::GetInstance()->Open();
	CTCPClient_CE::GetInstance()->Connect();
}
/**
*@brief project�������£�Ԥ����ҵ�ļ�
*�������ƣ�ProjectHandle
*�������ܣ�project�������£�Ԥ����ҵ�ļ�
**/
void TeachBoxKeyHandle::ProjectHandle(void*)
{
	m_bflag2=1;///<����Ƿ��ǵ�һ�ΰ���
	GKW=KEYPROJECT;
	if (m_bflag1)
	{
		CListUI* pFileNameList=HwndHandle::pOpenFileWnd->m_FileNameList;
		CJobInterface *pRobotJob=m_pMainUI->m_pJobDisplay->pRobotJob;
		std::vector<TSTRING> vec=pRobotJob->getJobFileNameVector();
		HwndHandle::pOpenFileWnd->AddAllFileListItem(vec);
		if (pFileNameList->GetCount()>0)
		{
			pFileNameList->SelectItem(0);
		}
		::ShowWindow(HwndHandle::pOpenFileWnd->GetHWND(),SW_SHOW);
		if(USLM==OPERATOR)
		{
			m_pMainUI->m_pFileButtonState->SetFileButtonState(CFileButtonState::bsInitPro1);

		}
		else{
			m_pMainUI->m_pFileButtonState->SetFileButtonState(CFileButtonState::bsInitPro);

		}
		m_bflag1=0;
	}
	else
	{
		m_pMainUI->m_pFileButtonState->SetFileButtonState(CFileButtonState::bsExit);
	}
}
/**
*@brief file�������£��½���ҵ�ļ�
*�������ƣ�NewFileHandle
*�������ܣ�file�������£��½���ҵ�ļ�
**/
void TeachBoxKeyHandle::NewFileHandle(void*)
{
	m_bflag1=1;///<����Ƿ��ǵ�һ�ΰ���
	GKW=KEYNEWFILE;
	if (m_bflag2)
	{
		m_pMainUI->m_pFileButtonState->SetFileButtonState(CFileButtonState::bsInit);
		m_bflag2=0;
	}
	else
	{
		m_pMainUI->m_pFileButtonState->SetFileButtonState(CFileButtonState::bsExit);
	}
	::ShowWindow(HwndHandle::pOpenFileWnd->GetHWND(),SW_HIDE);
}
/**
*@brief �㶯����
*�������ƣ�AxisControlHandle
*�������ܣ��㶯����
**/
void TeachBoxKeyHandle::AxisControlHandle(void* num)
{
	m_bKeyUpFlag=1;
	AXIS *axis=(AXIS*)(num);
	m_pMainUI->m_pRobot->m_pAxisControl->sendAxisControlInstr(*axis);
}
/**
*@brief �رս���
*�������ƣ�ShutDownHandle1
*�������ܣ��رս���
**/
void TeachBoxKeyHandle::ShutDownHandle1(void*)
{
	m_bShutDow=1;
}
/**
*@brief �رս���
*�������ƣ�ShutDownHandle2
*�������ܣ��رս���
**/
void TeachBoxKeyHandle::ShutDownHandle2(void*)
{
	if (m_bShutDow)
	{	
		if(m_pMainUI->m_pRobot->m_pServe->GetState()==CRobotStateValue::SERVEOFF)
		{
			PostQuitMessage(0);
		}
		else
		{
			HwndHandle::pDisplayTips->DisplayTips(CTips::tipsInfoProduct,PLEASE_SERVE_OFF);
			m_bShutDow=0;
		}
	}
}
























