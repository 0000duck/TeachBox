/**
 *@file
 *文件名称：CCommunication.cpp
 *
 *摘要：负责传送指定类型的字符串，例如机器人运动指令
 *关节数据等
 *
 *@author fly1992@163.com
 *
 **/
#include "CCommunication.h"
CCommunication::CCommunication()
{

}
///初始化客户端对象套接字
CTCPClient_CE* CCommunication::m_pTCPIPClient=CTCPClient_CE::GetInstance();
/**
 *@brief 发送数据
 *函数名称：SendData
 *函数功能：发送机器人指定类型的数据
 *
 * @param CRobotDataType* 机器人数据类型  
 * @return true发送成功 false发送失败
 **/
bool CCommunication::SendData(CRobotDataType* robotDataType)
{
	string strTemp=robotDataType->GetRobotDataStr();
	if (m_pTCPIPClient->SendData(strTemp.c_str(),strTemp.length()))
	{
		return true;
	}
	else
		return false;
}
/**
 *@brief 接收数据
 *函数名称：ReceiverData
 *函数功能：接收服务器类型的数据 
 *
 * @return string 接收控制器发送过来的数据
 **/
std::string CCommunication::ReceiverData()
{
	return m_pTCPIPClient->GetStrRecvBuf();
}

