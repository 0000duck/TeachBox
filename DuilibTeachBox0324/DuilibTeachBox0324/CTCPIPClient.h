/**
*@file
*文件名称：CTCPIPCLient.cpp
*
*摘要：用于封装TCP套接字客户端通讯
*
*@author 汪兵 modified by fly1992@163.com
*
**/
#pragma once
#include <winsock.h>
#include <string>
#include "GlobalVar.h"
const int BUFFERNUMBER=4096;///<接收缓冲区字符数组的长度
class CTCPClient_CE
{
public:
	~CTCPClient_CE(void);

public:
	CStdString m_remoteHost;///<远程主机IP地址
	int  m_port;///<远程主机端口
	BYTE *m_pRecvBuf; ///<接收字符缓存地址
	HANDLE m_tcpReceHandle;///<通讯接收事件句柄
	static BOOL m_ConnectFlag;///<通信连接标志位，用于形成客户端和服务器握手

public:
	BOOL Open();///<用于打开客户端socket
	BOOL Close();///<用于关闭客户端socket
	BOOL Connect();///<用于建立与TCP服务器连接
	std::string GetStrRecvBuf();///获得接收缓存内的字符串
	BOOL SendData(const char * buf , DWORD dwBufLen);///<向服务器端发送数据
	static CTCPClient_CE* GetInstance();///<单例模式，获得静态对象句柄

private:
	CTCPClient_CE(void);
	void TCPRead(const char * buf,DWORD dwBufLen);///<客户端读取主机发送的字符
	static DWORD SocketThreadFunc(LPVOID lparam);///<通讯线程函数

private:
	SOCKET m_socket; ///<通讯Socket句柄     
	HANDLE m_exitThreadEvent;///<通讯线程退出事件句柄 
	HANDLE m_tcpThreadHandle;///<通讯线程句柄
	char m_recvBuf[BUFFERNUMBER];///<接收缓冲区
	HANDLE m_tcpReceEvent;///<通讯接受事件句柄
	static CTCPClient_CE* m_TcpClient;

private:
	class DestroyInstance ///<用于析构CTCPClient类的对象
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
