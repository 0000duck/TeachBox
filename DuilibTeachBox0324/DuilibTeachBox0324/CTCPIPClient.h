/**
*@file
*�ļ����ƣ�CTCPIPCLient.cpp
*
*ժҪ�����ڷ�װTCP�׽��ֿͻ���ͨѶ
*
*@author ���� modified by fly1992@163.com
*
**/
#pragma once
#include <winsock.h>
#include <string>
#include "GlobalVar.h"
const int BUFFERNUMBER=4096;///<���ջ������ַ�����ĳ���
class CTCPClient_CE
{
public:
	~CTCPClient_CE(void);

public:
	CStdString m_remoteHost;///<Զ������IP��ַ
	int  m_port;///<Զ�������˿�
	BYTE *m_pRecvBuf; ///<�����ַ������ַ
	HANDLE m_tcpReceHandle;///<ͨѶ�����¼����
	static BOOL m_ConnectFlag;///<ͨ�����ӱ�־λ�������γɿͻ��˺ͷ���������

public:
	BOOL Open();///<���ڴ򿪿ͻ���socket
	BOOL Close();///<���ڹرտͻ���socket
	BOOL Connect();///<���ڽ�����TCP����������
	std::string GetStrRecvBuf();///��ý��ջ����ڵ��ַ���
	BOOL SendData(const char * buf , DWORD dwBufLen);///<��������˷�������
	static CTCPClient_CE* GetInstance();///<����ģʽ����þ�̬������

private:
	CTCPClient_CE(void);
	void TCPRead(const char * buf,DWORD dwBufLen);///<�ͻ��˶�ȡ�������͵��ַ�
	static DWORD SocketThreadFunc(LPVOID lparam);///<ͨѶ�̺߳���

private:
	SOCKET m_socket; ///<ͨѶSocket���     
	HANDLE m_exitThreadEvent;///<ͨѶ�߳��˳��¼���� 
	HANDLE m_tcpThreadHandle;///<ͨѶ�߳̾��
	char m_recvBuf[BUFFERNUMBER];///<���ջ�����
	HANDLE m_tcpReceEvent;///<ͨѶ�����¼����
	static CTCPClient_CE* m_TcpClient;

private:
	class DestroyInstance ///<��������CTCPClient��Ķ���
	{
	public:
		~DestroyInstance()
		{
			if (m_TcpClient!=NULL)
			{
				delete m_TcpClient;
				m_TcpClient=NULL;
			}
		}
	};
	static DestroyInstance DI;
};
