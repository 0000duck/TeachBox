/**
 *@file
 *�ļ����ƣ�CCommunication.h
 *
 *ժҪ��������ָ�����͵��ַ���������������˶�ָ��
 *�ؽ����ݵ�
 *
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include <string>
#include "CTCPIPClient.h"
#include "CRobotDataType.h"
///ͨѶ����ɶ�CTCPClient_CE��ķ�װ��������ģʽ�������ͺͽ��ܶ˿�
class CCommunication
{
public:
	CCommunication();
	bool SendData(CRobotDataType* robotDataType);
	std::string ReceiverData();
private:
	static CTCPClient_CE* m_pTCPIPClient;
};

