/**
 *@file
 *�ļ����ƣ�CCommunication.cpp
 *
 *ժҪ��������ָ�����͵��ַ���������������˶�ָ��
 *�ؽ����ݵ�
 *
 *@author fly1992@163.com
 *
 **/
#include "CCommunication.h"
CCommunication::CCommunication()
{

}
///��ʼ���ͻ��˶����׽���
CTCPClient_CE* CCommunication::m_pTCPIPClient=CTCPClient_CE::GetInstance();
/**
 *@brief ��������
 *�������ƣ�SendData
 *�������ܣ����ͻ�����ָ�����͵�����
 *
 * @param CRobotDataType* ��������������  
 * @return true���ͳɹ� false����ʧ��
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
 *@brief ��������
 *�������ƣ�ReceiverData
 *�������ܣ����շ��������͵����� 
 *
 * @return string ���տ��������͹���������
 **/
std::string CCommunication::ReceiverData()
{
	return m_pTCPIPClient->GetStrRecvBuf();
}

