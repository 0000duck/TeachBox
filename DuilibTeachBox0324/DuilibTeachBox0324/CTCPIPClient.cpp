/**
*@file
*�ļ����ƣ�CTCPIPCLient.cpp
*
*ժҪ�����ڷ�װTCP�׽��ֿͻ���ͨѶ
*
*@author ���� modified by fly1992@163.com
*
**/
#include "StdAfx.h"
#include "CTCPIPClient.h"
///��̬������ʼ��
CTCPClient_CE *CTCPClient_CE::m_TcpClient=NULL;
CTCPClient_CE::DestroyInstance CTCPClient_CE::DI;
BOOL CTCPClient_CE::m_ConnectFlag=0;
/**
*@file
*�������ƣ����캯��CTCPClient_CE
*�������ܣ���ʼ��socket����,�ÿջ�����
*�����߳��˳��¼����,����һ���Զ��¼�,�������ź�״̬
**/
CTCPClient_CE::CTCPClient_CE()///<���캯��
{
	WSADATA wsd;
	WSAStartup(MAKEWORD(2,2),&wsd);///<��ʼ��socket����
	ZeroMemory(m_recvBuf,BUFFERNUMBER);///<�ÿջ�����
	m_pRecvBuf=NULL;
	///�����߳��˳��¼����
	m_exitThreadEvent = CreateEvent(NULL,FALSE,FALSE,L"EVENT_TCP_CLIENT_THREAD");
	///����һ���Զ��¼����������ź�״̬������ΪEVENT_TCP_CLIENT_THREAD
	m_tcpReceEvent=CreateEvent(NULL,FALSE,FALSE,L"EVENT_TCP_RECE_THREAD");
	///��ip��ַ�Ͷ˿ں�
	m_remoteHost=HostIP;
	m_port=PORT;
}

/**
*@file
*�������ƣ���������~CTCPClient_CE
*�������ܣ���ʼ��socket����,�ÿջ�����
*�����߳��˳��¼����,����һ���Զ��¼�,�������ź�״̬
*
**/
CTCPClient_CE::~CTCPClient_CE()
{
	///�ر��߳��˳��¼����
	CloseHandle(m_exitThreadEvent);
	///�ر��߳̽����¼���Դ
	CloseHandle(m_tcpReceEvent);
	///�ͷ�socket��Դ
	WSACleanup();
	if (m_pRecvBuf!=NULL)
	{
		delete [] m_pRecvBuf;
		m_pRecvBuf=NULL;
	}
}

/**
*@file
*�������ƣ�SocketThreadFunc
*�������ܣ����߳����ڼ���TCP�ͻ���ͨѶ���¼������統���յ����ݡ�
*���ӶϿ���ͨѶ���̷���������¼�
*
* @param lparam ������ָ�룬����ͨ���˲��������߳��д�����Ҫ�õ�����Դ��
*  
* @return ����ֵû���ر�����壬�ڴ����ǽ�����ֵ��Ϊ0
**/
DWORD CTCPClient_CE::SocketThreadFunc(LPVOID lparam)
{
	CTCPClient_CE *pSocket;
	pSocket = (CTCPClient_CE*)lparam;///<�õ�CTCPClient_CEʵ��ָ��

	fd_set fdRead;///<������¼�����
	int ret;
	TIMEVAL	aTime;///<�����¼��ȴ�ʱ��
	aTime.tv_sec = 1;
	aTime.tv_usec = 0;
	while (TRUE)
	{
		///�յ��˳��¼��������߳�
		if (WaitForSingleObject(pSocket->m_exitThreadEvent,0) == WAIT_OBJECT_0)
		{
			break;
		}
		///�ÿ�fdRead�¼�Ϊ��
		FD_ZERO(&fdRead);
		FD_SET(pSocket->m_socket,&fdRead);///<���ͻ���socket���ö��¼�
		ret = select(0,&fdRead,NULL,NULL,&aTime);///<����select�������ж��Ƿ��ж��¼�����
		if (ret == SOCKET_ERROR)
		{
			m_ConnectFlag=0;
			closesocket(pSocket->m_socket);
			break;
		}
		if (ret > 0)
		{

			if (FD_ISSET(pSocket->m_socket,&fdRead))///<�������¼�
			{
				ZeroMemory(pSocket->m_recvBuf,BUFFERNUMBER);
				///��������
				int recvLen = recv(pSocket->m_socket,pSocket->m_recvBuf, BUFFERNUMBER,0); 
				if (recvLen == SOCKET_ERROR)
				{
					int iError = WSAGetLastError();
					m_ConnectFlag=0;///<ͨ�ŶϿ�
					closesocket(pSocket->m_socket);	///<�رտͻ���socket
					break;
				}
				else if (recvLen == 0)
				{	
					m_ConnectFlag=0;///<ͨ�ŶϿ�
					closesocket(pSocket->m_socket);///<�رտͻ���socket
					break;
				}
				else
				{		
					pSocket->TCPRead(pSocket->m_recvBuf,recvLen);///<�������ݽ����¼�
				}
			}
		}
	}
	TRACE(L"�ͻ����߳��˳�\n");
	return 0;
}
/**
*@file
*�������ƣ�Open
*�������ܣ����ڴ򿪿ͻ���socket
*
*@return TRUE:�򿪳ɹ�;FALSE:��ʧ��
**/
BOOL CTCPClient_CE::Open()
{

	ResetEvent(m_exitThreadEvent);///<��λ�߳��˳��¼�
	m_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);///<����TCP�׽��� 
	if (m_socket == SOCKET_ERROR)
	{
		return FALSE;
	}
	m_tcpThreadHandle = CreateThread(NULL,0,SocketThreadFunc,this,0,NULL);///<����ͨѶ�߳�
	if (m_tcpThreadHandle == NULL)
	{
		closesocket(m_socket);
		return FALSE;
	}
	return TRUE;
}
/**
*@file
*�������ƣ�Close
*�������ܣ����ڹرտͻ���socket
*
*@return TRUE:�رճɹ�;FALSE:�ر�ʧ��
**/
BOOL CTCPClient_CE::Close()
{
	///����ͨѶ�߳̽����¼�
	SetEvent(m_exitThreadEvent);

	///�ȴ�1�룬������߳�û���˳�����ǿ���˳�
	if (WaitForSingleObject(m_tcpThreadHandle,1000) == WAIT_TIMEOUT)
	{
		TerminateThread(m_tcpThreadHandle,0);
		TRACE(L"ǿ����ֹ�ͻ����߳�\n");
	}
	m_tcpThreadHandle = NULL;
	///�ر�Socket���ͷ���Դ
	int err = closesocket(m_socket);
	if (err == SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;
}
/**
*@file
*�������ƣ�Connect
*�������ܣ����ڽ�����TCP����������
*
* @return TRUE:�������ӳɹ�;FALSE:��������ʧ��
**/
BOOL CTCPClient_CE::Connect()
{
	struct sockaddr_in addr;
	int err;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_port);
	///�˴�Ҫ��˫�ֽ�ת���ɵ��ֽ�
	char ansiRemoteHost[255];
	ZeroMemory(ansiRemoteHost,255);
	WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,m_remoteHost,wcslen(m_remoteHost)
		,ansiRemoteHost,wcslen(m_remoteHost),NULL,NULL);

	addr.sin_addr.s_addr=inet_addr(ansiRemoteHost);
	///��ʱ����ͬ�����ӷ�ʽ,connectֱ�ӷ��سɹ�����ʧ��
	err = connect(m_socket,(struct sockaddr *)&addr,sizeof(addr));
	if (err == SOCKET_ERROR) 
	{
		return FALSE;
	}
	///����ͨѶģʽΪ�첽ģʽ
	DWORD ul= 1;
	ioctlsocket(m_socket,FIONBIO,&ul);
	m_ConnectFlag=1;
	return TRUE;
}
/**
*@file
*�������ƣ�SendData
*�������ܣ���������˷�������
*
* @param buf �����͵�����
* @param b dwBufLen �����͵����ݳ���
* @return TRUE:�������ݳɹ�;FALSE:��������ʧ��
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
			m_ConnectFlag=0;///<ͨ�ű�־���㣬��ʾ�Ͽ�����
			Close();///<�ر�socket
			return FALSE;
		}

		///�ۼƷ��͵��ֽ���
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
*�������ƣ�GetInstance
*�������ܣ���ȡCTCPClient_CE�����ָ��
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
*�������ƣ�TCPRead
*�������ܣ����ݳɹ����գ���λ�¼��ź�
*
* @param buf ���ݽ��ջ�����ָ��
* @param bdwBufLen ���ݳ��� 
**/
void CTCPClient_CE::TCPRead(const char * buf,DWORD dwBufLen)
{
	BYTE *pRecvBuf = NULL; //���ջ�����
	///�����յĻ�����������pRecvBuf��
	pRecvBuf = new BYTE[dwBufLen];
	CopyMemory(pRecvBuf,buf,dwBufLen);
	///�����첽��Ϣ����ʾ�յ�TCP���ݣ���Ϣ�����꣬Ӧ�ͷ��ڴ�
	SetEvent(m_tcpReceEvent);
}
/**
*@file
*�������ƣ�GetStrRecvBuf
*�������ܣ���ȡ���������ַ���
*
* @return string ���յ����ַ���
**/
std::string CTCPClient_CE::GetStrRecvBuf()
{
	ResetEvent(m_tcpReceEvent);///<һֱ����ȴ� ��Resetevent�̵߳��÷�
	WaitForSingleObject(m_tcpReceEvent,INFINITE);
	return m_recvBuf;
}
