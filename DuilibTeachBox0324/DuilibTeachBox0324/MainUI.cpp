#include "MainUI.h"
#include "CHandleWnd.h"
/**
 *@brief 构造函数
 *函数名称：CMainFrameRobotDlg
 *函数功能：构造函数
 **/
CMainFrameRobotDlg::CMainFrameRobotDlg(void)
{
	m_pFileButtonControl=new FileButtonControl;
	m_pStateControl=new StateControl;
	m_pCoordControl=new CoordControl;
	m_pRobot=new CRobot;
	
	KeyPadWnd* keyPadWnd=KeyPadWnd::GetHandle(NULL);///<加载软件盘
	keyPadWnd->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, 0, 0, 0, 0, 0, NULL);
}

CMainFrameRobotDlg::~CMainFrameRobotDlg(void)
{

}
/**
*@brief 设置窗口名称
*函数名称：GetWindowClassName
*函数功能：设置窗口名称
**/
LPCTSTR CMainFrameRobotDlg::GetWindowClassName() const
{
	return _T("MainFrameRobot");
}
/**
*@brief windows消息处理函数
*函数名称：HandleMessage
*函数功能：windows消息处理函数
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
*@brief 加载XML文件，创建窗口
*函数名称：OnCreate
*函数功能：加载XML文件，创建窗口
**/
LRESULT CMainFrameRobotDlg::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	m_PaintManager.Init(m_hWnd);
	m_PaintManager.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("MainUI.xml"), (UINT)0, NULL, &m_PaintManager);   // DemoSkin.xml需要放到exe目录下
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);   ///< 添加控件等消息响应，这样消息就会传达到duilib的消息循环，我们可以在Notify函数里做消息处理
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
 *@brief 各种控件通知消息处理函数
 *函数名称：Notify
 *函数功能：各种控件通知消息处理函数
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
 *@brief 初始化各种示教文件编辑按键
 *函数名称：InitFileButtonControl
 *函数功能：初始化各种示教文件编辑按键，如新建，插入，删除，setPC等
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
 *@brief 初始化各种状态控件
 *函数名称：InitStateControl
 *函数功能：初始化各种状态控件，获得对应的指针，如伺服状态等
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
 *@brief 坐标控件的初始化动作
 *函数名称：InitCoordControl
 *函数功能：坐标控件的初始化动作，初始化六轴，同步模式下，应该能够翻页
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
 *@brief 完成复杂控件的初始化动作
 *函数名称：InitComplicateControl
 *函数功能：完成复杂控件的初始化动作，像组合框、列表等，获得相应的指针
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
 *@brief 完成主界面各种控件的初始化工作
 *函数名称：Init
 *函数功能：完成主界面各种控件的初始化工作，获得响应的指针
 **/
void CMainFrameRobotDlg::Init()
{
	InitFileButtonControl();
	InitStateControl();
	InitCoordControl();
	CMainFrameRobotDlg::InitComplicateControl();
	TECH_BOX_ERR_CODE TEACHINIT=TechBoxLibInit(this->m_hWnd,WM_TECHBOX_KEY_CHANGE,WM_TECHBOX_MPG);

	HwndHandle::pNewFileWnd=new CNewFileWnd;///<创建新建窗口
	HwndHandle::pNewFileWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0, 1,86, 0, 0, NULL);
	::ShowWindow(*HwndHandle::pNewFileWnd,SW_HIDE);

	HwndHandle::pInsertWnd=new CInsertWnd;///<创建插入窗口
	HwndHandle::pInsertWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0, 1,86, 0, 0, NULL);
	::ShowWindow(*HwndHandle::pInsertWnd,SW_HIDE);

	HwndHandle::pOpenFileWnd=new COpenFileWnd;///<创建插入窗口
	HwndHandle::pOpenFileWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0,1,86 , 0, 0, NULL);
	::ShowWindow(*HwndHandle::pOpenFileWnd,SW_HIDE);


	HwndHandle::pMainFrameRobotDlg=this;///<传递主窗口句柄

	HWND hWnd=::FindWindow(_T("HHTaskBar"),NULL);
	::ShowWindow(hWnd,SW_HIDE);///<隐藏任务栏
}

void CMainFrameRobotDlg::OnWindowInit()
{
	HwndHandle::pLoginWnd=new CLoginWnd;///<创建插入窗口
	HwndHandle::pLoginWnd->Create(m_hWnd, _T(""), UI_WNDSTYLE_FRAME, 0, 0, 0, 0, 0, NULL);
	HwndHandle::pLoginWnd->ShowModal();
}
/**
 *@brief 完成示教文件编辑按钮的响应
 *函数名称：OnLBtnClick
 *函数功能：完成示教文件编辑按钮的响应
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
 *@brief 此处主要处理按键消息响应
 *函数名称：MessageHandler
 *函数功能：此处主要处理按键消息响应
 *@return LRESULT 处理结果
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
///物理按键处理类单例模式指针变量
TeachBoxKeyHandle* TeachBoxKeyHandle::teachBoxHandle=NULL;
///物理按键处理类构造函数
TeachBoxKeyHandle::TeachBoxKeyHandle(CMainFrameRobotDlg* pMain):m_pMainUI(pMain)
{
	for (int i=0;i<KEYNUMBER;i++)
	{
		KeyHandle[i]=NULL;
	}
	CreateMapKeyHandle();///<创建物理按键响应映射关系
	m_pMainUI->m_pRobot->m_pCoord->SetCoordControl(m_pMainUI->m_pCoordControl);
	///<用于设置各个轴坐标标志
	m_bflag1=1;
	m_bflag2=1;
	m_bKeyUpFlag=0;
	m_bShutDow=0;

}
/**
 *@brief 获取物理按键处理类单例模式指针变量
 *函数名称：GetHandle
 *函数功能：获取物理按键处理类单例模式指针变量
 * @param CMainFrameRobotDlg* 对话框指针
 * @return 物理按键处理类单例模式指针变量
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
 *@brief 设置伺服状态
 *函数名称：ServeHandle
 *函数功能：设置伺服状态
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
		CoordHandle(NULL);///<设为用户坐标
		bflag=0;
	}
	
}
/**
 *@brief 示教速度设置 
 *函数名称：SpeedHandle
 *函数功能：示教速度设置
 **/
void TeachBoxKeyHandle::SpeedHandle(void*)
{
	m_pMainUI->m_pRobot->DisplayState(CRobot::m_pSpeed,
		m_pMainUI->m_pStateControl->m_pRobotSpeedText,
		m_pMainUI->m_pStateControl->m_pRobotSpeedIcon);
}
/**
 *@brief 坐标类型设置
 *函数名称：CoordHandle
 *函数功能：坐标类型设置
 **/
void TeachBoxKeyHandle::CoordHandle(void*)
{
	m_pMainUI->m_pRobot->DisplayState(CRobot::m_pCoord,
		m_pMainUI->m_pStateControl->m_pRobotCoordText,
		m_pMainUI->m_pStateControl->m_pRobotCoordIcon);
}
/**
 *@brief 同步模式设置
 *函数名称：SyncHandle
 *函数功能：同步模式设置
 **/
void TeachBoxKeyHandle::SyncHandle(void*)
{
	m_pMainUI->m_pRobot->DisplayState(CRobot::m_pSync,
		m_pMainUI->m_pStateControl->m_pRobotSyncText,
		m_pMainUI->m_pStateControl->m_pRobotSyncIcon);
}

/**
 *@brief 机器人模式设置
 *函数名称：ModelHandle
 *函数功能：机器人模式设置
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
 *@brief 机器人再现按钮设置
 *函数名称：StartHandle
 *函数功能：机器人再现按钮设置
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
 *@brief 机器人示教按钮设置
 *函数名称：StepHandle
 *函数功能：是机器人示教按钮设置
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
 *@brief 设置机器人对象
 *函数名称：RobotObjHandle
 *函数功能：设置机器人对象
 **/
void TeachBoxKeyHandle::RobotObjHandle(void*)
{
	m_pMainUI->m_pRobot->DisplayState(CRobot::m_pRobotObj,
		m_pMainUI->m_pStateControl->m_pRobotObjText,
		m_pMainUI->m_pStateControl->m_pRobotObjIcon);
}
/**
 *@brief 建立物理按键和对应相应函数之间的映射
 *函数名称：CreateMapKeyHandle
 *函数功能：建立物理按键和对应相应函数之间的映射
 **/
void TeachBoxKeyHandle::CreateMapKeyHandle(void)
{
	int ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYSERVE);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::ServeHandle;///<指明所属类TeachBoxKeyHandle
	
	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYSPEED);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::SpeedHandle;///<指明所属类TeachBoxKeyHandle

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYCOORD);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::CoordHandle;///<指明所属类TeachBoxKeyHandle

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYROBOT);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::RobotObjHandle;///<指明所属类TeachBoxKeyHandle

	ikeyIndex=GetTeachBoxKeyIndex(CTeachBoxKeyValue::KEYSYNC);
	KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::SyncHandle;///<指明所属类TeachBoxKeyHandle

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
	///根据需要自行添加函数相应映射,尝试改成map，简化代码
	for (int i=0,j=CTeachBoxKeyValue::KEYAXISSM;i<NUMAXISCONTROL;i++)
	{
		ikeyIndex=GetTeachBoxKeyIndex(j);
		j=j<<1;
		KeyHandle[ikeyIndex]=&TeachBoxKeyHandle::AxisControlHandle;
	}
}
/**
 *@brief 物理按键响应函数
 *函数名称：KeyMessageHandle
 *函数功能：物理按键响应函数
 * @param ikeyValue 物理按键键值 
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
		///添加错误提示
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
	if (ikeyValue==CTeachBoxKeyValue::KEYUP)///<按键弹出时候的响应
	{
		if (m_bKeyUpFlag)
		{
			m_pMainUI->m_pRobot->m_pAxisControl->sendAxisControlInstr(AXISSTOP);
			m_bKeyUpFlag=0;
		}
		return;
	}
	if (keyIndex>=9&&keyIndex<=20)//各个轴的响应
	{
		int num=keyIndex-9;
		(this->*KeyHandle[keyIndex])((void*)&num);
	}
	else if(KeyHandle[keyIndex])
	{
		(this->*KeyHandle[keyIndex])(NULL);///<一定要添加this指针，并且加*号
	}	
}

/**
 *@brief 获取物理按键响应函数在函数指针数组中的索引
 *函数名称：GetTeachBoxKeyIndex
 *函数功能：获取物理按键响应函数在函数指针数组中的索引
 * @param keyValue 物理按键的键值
 * @return index 索引值 
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
 *@brief 测试TCPIP通信连接
 *函数名称：TcpConnect
 *函数功能：测试TCPIP通信连接
 **/
void TeachBoxKeyHandle::TcpConnect(void*)
{
	CTCPClient_CE::GetInstance()->Open();
	CTCPClient_CE::GetInstance()->Connect();
}
/**
*@brief project按键按下，预览作业文件
*函数名称：ProjectHandle
*函数功能：project按键按下，预览作业文件
**/
void TeachBoxKeyHandle::ProjectHandle(void*)
{
	m_bflag2=1;///<辨别是否是第一次按下
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
*@brief file按键按下，新建作业文件
*函数名称：NewFileHandle
*函数功能：file按键按下，新建作业文件
**/
void TeachBoxKeyHandle::NewFileHandle(void*)
{
	m_bflag1=1;///<辨别是否是第一次按下
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
*@brief 点动控制
*函数名称：AxisControlHandle
*函数功能：点动控制
**/
void TeachBoxKeyHandle::AxisControlHandle(void* num)
{
	m_bKeyUpFlag=1;
	AXIS *axis=(AXIS*)(num);
	m_pMainUI->m_pRobot->m_pAxisControl->sendAxisControlInstr(*axis);
}
/**
*@brief 关闭界面
*函数名称：ShutDownHandle1
*函数功能：关闭界面
**/
void TeachBoxKeyHandle::ShutDownHandle1(void*)
{
	m_bShutDow=1;
}
/**
*@brief 关闭界面
*函数名称：ShutDownHandle2
*函数功能：关闭界面
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
























