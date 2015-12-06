/**
*@file
*文件名称：CTCPIPCLient.cpp
*
*摘要：用于封装TCP套接字客户端通讯
*
*@author 汪兵 modified by fly1992@163.com
*
**/
#include "StdAfx.h"
#include "CTCPIPClient.h"
///静态变量初始化
CTCPClient_CE *CTCPClient_CE::m_TcpClient=NULL;
CTCPClient_CE::DestroyInstance CTCPClient_CE::DI;
BOOL CTCPClient_CE::m_ConnectFlag=0;
/**
*@file
*函数名称：构造函数CTCPClient_CE
*函数功能：初始化socket环境,置空缓冲区
*创建线程退出事件句柄,创建一个自动事件,处于无信号状态
**/
CTCPClient_CE::CTCPClient_CE()///<构造函数
{
	WSADATA wsd;
	WSAStartup(MAKEWORD(2,2),&wsd);///<初始化socket环境
	ZeroMemory(m_recvBuf,BUFFERNUMBER);///<置空缓冲区
	m_pRecvBuf=NULL;
	///创建线程退出事件句柄
	m_exitThreadEvent = CreateEvent(NULL,FALSE,FALSE,L"EVENT_TCP_CLIENT_THREAD");
	///创建一个自动事件，处于无信号状态，名字为EVENT_TCP_CLIENT_THREAD
	m_tcpReceEvent=CreateEvent(NULL,FALSE,FALSE,L"EVENT_TCP_RECE_THREAD");
	///绑定ip地址和端口号
	m_remoteHost=HostIP;
	m_port=PORT;
}

/**
*@file
*函数名称：析构函数~CTCPClient_CE
*函数功能：初始化socket环境,置空缓冲区
*创建线程退出事件句柄,创建一个自动事件,处于无信号状态
*
**/
CTCPClient_CE::~CTCPClient_CE()
{
	///关闭线程退出事件句柄
	CloseHandle(m_exitThreadEvent);
	///关闭线程接受事件资源
	CloseHandle(m_tcpReceEvent);
	///释放socket资源
	WSACleanup();
	if (m_pRecvBuf!=NULL)
	{
		delete [] m_pRecvBuf;
		m_pRecvBuf=NULL;
	}
}

/**
*@file
*函数名称：SocketThreadFunc
*函数功能：此线程用于监听TCP客户端通讯的事件，例如当接收到数据、
*连接断开和通讯过程发生错误等事件
*
* @param lparam 无类型指针，可以通过此参数，向线程中传入需要用到的资源。
*  
* @return 返回值没有特别的意义，在此我们将返回值设为0
**/
DWORD CTCPClient_CE::SocketThreadFunc(LPVOID lparam)
{
	CTCPClient_CE *pSocket;
	pSocket = (CTCPClient_CE*)lparam;///<得到CTCPClient_CE实例指针

	fd_set fdRead;///<定义读事件集合
	int ret;
	TIMEVAL	aTime;///<定义事件等待时间
	aTime.tv_sec = 1;
	aTime.tv_usec = 0;
	while (TRUE)
	{
		///收到退出事件，结束线程
		if (WaitForSingleObject(pSocket->m_exitThreadEvent,0) == WAIT_OBJECT_0)
		{
			break;
		}
		///置空fdRead事件为空
		FD_ZERO(&fdRead);
		FD_SET(pSocket->m_socket,&fdRead);///<给客户端socket设置读事件
		ret = select(0,&fdRead,NULL,NULL,&aTime);///<调用select函数，判断是否有读事件发生
		if (ret == SOCKET_ERROR)
		{
			m_ConnectFlag=0;
			closesocket(pSocket->m_socket);
			break;
		}
		if (ret > 0)
		{

			if (FD_ISSET(pSocket->m_socket,&fdRead))///<发生读事件
			{
				ZeroMemory(pSocket->m_recvBuf,BUFFERNUMBER);
				///接收数据
				int recvLen = recv(pSocket->m_socket,pSocket->m_recvBuf, BUFFERNUMBER,0); 
				if (recvLen == SOCKET_ERROR)
				{
					int iError = WSAGetLastError();
					m_ConnectFlag=0;///<通信断开
					closesocket(pSocket->m_socket);	///<关闭客户端socket
					break;
				}
				else if (recvLen == 0)
				{	
					m_ConnectFlag=0;///<通信断开
					closesocket(pSocket->m_socket);///<关闭客户端socket
					break;
				}
				else
				{		
					pSocket->TCPRead(pSocket->m_recvBuf,recvLen);///<触发数据接收事件
				}
			}
		}
	}
	TRACE(L"客户端线程退出\n");
	return 0;
}
/**
*@file
*函数名称：Open
*函数功能：用于打开客户端socket
*
*@return TRUE:打开成功;FALSE:打开失败
**/
BOOL CTCPClient_CE::Open()
{

	ResetEvent(m_exitThreadEvent);///<复位线程退出事件
	m_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);///<创建TCP套接字 
	if (m_socket == SOCKET_ERROR)
	{
		return FALSE;
	}
	m_tcpThreadHandle = CreateThread(NULL,0,SocketThreadFunc,this,0,NULL);///<创建通讯线程
	if (m_tcpThreadHandle == NULL)
	{
		closesocket(m_socket);
		return FALSE;
	}
	return TRUE;
}
/**
*@file
*函数名称：Close
*函数功能：用于关闭客户端socket
*
*@return TRUE:关闭成功;FALSE:关闭失败
**/
BOOL CTCPClient_CE::Close()
{
	///发送通讯线程结束事件
	SetEvent(m_exitThreadEvent);

	///等待1秒，如果读线程没有退出，则强制退出
	if (WaitForSingleObject(m_tcpThreadHandle,1000) == WAIT_TIMEOUT)
	{
		TerminateThread(m_tcpThreadHandle,0);
		TRACE(L"强制终止客户端线程\n");
	}
	m_tcpThreadHandle = NULL;
	///关闭Socket，释放资源
	int err = closesocket(m_socket);
	if (err == SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;
}
/**
*@file
*函数名称：Connect
*函数功能：用于建立与TCP服务器连接
*
* @return TRUE:建立连接成功;FALSE:建立连接失败
**/
BOOL CTCPClient_CE::Connect()
{
	struct sockaddr_in addr;
	int err;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_port);
	///此处要将双字节转换成单字节
	char ansiRemoteHost[255];
	ZeroMemory(ansiRemoteHost,255);
	WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,m_remoteHost,wcslen(m_remoteHost)
		,ansiRemoteHost,wcslen(m_remoteHost),NULL,NULL);

	addr.sin_addr.s_addr=inet_addr(ansiRemoteHost);
	///此时采用同步连接方式,connect直接返回成功或是失败
	err = connect(m_socket,(struct sockaddr *)&addr,sizeof(addr));
	if (err == SOCKET_ERROR) 
	{
		return FALSE;
	}
	///设置通讯模式为异步模式
	DWORD ul= 1;
	ioctlsocket(m_socket,FIONBIO,&ul);
	m_ConnectFlag=1;
	return TRUE;
}
/**
*@file
*函数名称：SendData
*函数功能：向服务器端发送数据
*
* @param buf 待发送的数据
* @param b dwBufLen 待发送的数据长度
* @return TRUE:发送数据成功;FALSE:发送数据失败
**/
BOOL CTCPClient_CE::SendData(const char * buf , DWORD dwBufLen)
{
	int nBytes = 0;
	int nSendBytes=0;
	if (dwBufLen==80)
	{
		int a=100;
	}
	while ((DWORD)nSendBytes < dwBufLen)
	{
		nBytes = send(m_socket,buf+nSendBytes,dwBufLen-nSendBytes,0);
		if (nBytes==SOCKET_ERROR )
		{
			int iErrorCode = WSAGetLastError();
			m_ConnectFlag=0;///<通信标志置零，表示断开连接
			Close();///<关闭socket
			return FALSE;
		}

		///累计发送的字节数
		nSendBytes = nSendBytes + nBytes;

		if ((DWORD)nSendBytes < dwBufLen)
		{
			Sleep(1000);
		}
	} 
	return TRUE; 
}
/**
*@file
*函数名称：GetInstance
*函数功能：获取CTCPClient_CE对象的指针
*
**/
CTCPClient_CE* CTCPClient_CE::GetInstance()
{
	if (m_TcpClient==NULL)
	{
		m_TcpClient=new CTCPClient_CE();
	}
	return m_TcpClient;
}
/**
*@file
*函数名称：TCPRead
*函数功能：数据成功接收，置位事件信号
*
* @param buf 数据接收缓冲区指针
* @param bdwBufLen 数据长度 
**/
void CTCPClient_CE::TCPRead(const char * buf,DWORD dwBufLen)
{
	BYTE *pRecvBuf = NULL; //接收缓冲区
	///将接收的缓冲区拷贝到pRecvBuf种
	pRecvBuf = new BYTE[dwBufLen];
	CopyMemory(pRecvBuf,buf,dwBufLen);
	///发送异步消息，表示收到TCP数据，消息处理完，应释放内存
	SetEvent(m_tcpReceEvent);
}
/**
*@file
*函数名称：GetStrRecvBuf
*函数功能：获取缓冲区的字符串
*
* @return string 接收到的字符串
**/
std::string CTCPClient_CE::GetStrRecvBuf()
{
	ResetEvent(m_tcpReceEvent);///<一直让其等待 ，Resetevent线程的用法
	WaitForSingleObject(m_tcpReceEvent,INFINITE);
	return m_recvBuf;
}
