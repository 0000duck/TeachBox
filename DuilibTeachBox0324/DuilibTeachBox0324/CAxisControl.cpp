/**
*@file
*�ļ����ƣ�CAxisControl.cpp
*
*ժҪ����װ������Ŀ�����Ϣ��ָ�������Ϣ�Լ���ҵָ����Ϣ������
*
*@author fly1992@163.com
*
**/
#include "CAxisControl.h"
/**
*@brief    ���Ϳ�����Ϣ����
*�������ƣ�sendBaseControlInstr
*�������ܣ����ݲ�ͬ���������ͣ����Ͳ�ͬ�Ŀ�����Ϣ
*@param CRobotDataType*ָ����������
**/
void CBaseControl::sendBaseControlInstr(CRobotDataType* p)
{
	pCommu->SendData(p);
}
/**
*@brief    ���ܿ�����Ϣ����
*�������ƣ�receiveControlInstr
*�������ܣ����ܿ�����Ϣ����
**/
std::string CBaseControl::receiveControlInstr()
{
	return pCommu->ReceiverData();
}
/**
*@brief    �����������Ϣ����
*�������ƣ�sendAxisControlInstr
*�������ܣ����ݲ�ͬ�ᣬ���Ͳ�ͬ�Ŀ�����Ϣ
*@param AXISָ����
**/
void CAxisControl::sendAxisControlInstr(AXIS axis)
{
	CRobotDataType* p=InstrDataFactory::axisInstr[axis];
	sendBaseControlInstr(p);
}
/**
*@brief    ���Ͳ���ָ��ʱ�Ŀ�����Ϣ
*�������ƣ�sendInstrControlInstr
*�������ܣ����ݲ�ͬ����ָ����Ͳ�ͬ�Ŀ�����Ϣ
*@param INSTR����ָ������
**/
void CInstrControl::sendInstrControlInstr(INSTR axis)
{
	CRobotDataType* p=InstrDataFactory::insertInstr[axis];
	sendBaseControlInstr(p);
}
/**
*@brief    ������ҵ������Ϣ����
*�������ƣ�sendJobControlInstr
*�������ܣ����ݲ�ͬ��ҵ��䣬���Ͳ�ͬ�Ŀ�����Ϣ
*@param str��ҵ����ַ���
**/
void CJobControl::sendJobControlInstr(std::string str)
{
	CRobotDataType* p=new CRobotJointData(str);
	sendBaseControlInstr(p);
	Delayms(10);
	delete p;
}

