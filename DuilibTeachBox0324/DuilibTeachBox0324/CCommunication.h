/**
 *@file
 *文件名称：CCommunication.h
 *
 *摘要：负责传送指定类型的字符串，例如机器人运动指令
 *关节数据等
 *
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include <string>
#include "CTCPIPClient.h"
#include "CRobotDataType.h"
///通讯类完成对CTCPClient_CE类的封装，适配器模式留出发送和接受端口
class CCommunication
{
public:
	CCommunication();
	bool SendData(CRobotDataType* robotDataType);
	std::string ReceiverData();
private:
	static CTCPClient_CE* m_pTCPIPClient;
};

