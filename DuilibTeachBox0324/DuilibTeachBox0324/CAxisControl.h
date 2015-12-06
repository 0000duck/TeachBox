/**
*@file
*�ļ����ƣ�CAxisControl.h
*
*ժҪ����װ������Ŀ�����Ϣ��ָ�������Ϣ�Լ���ҵָ����Ϣ������
*
*@author fly1992@163.com
*
**/
#pragma  once
#include "GlobalVar.h"
#include "CCommunication.h"
#include "CRobotDataTypeFactory.h"
///������ģʽ����װ��ͨѶ�����ڷ��ͺͽ����ַ�
class CBaseControl
{
public:
	CBaseControl():pCommu(new CCommunication){};
	std::string receiveControlInstr();
protected:
	void sendBaseControlInstr(CRobotDataType* p);
private:
	CCommunication* pCommu;
};
///�������ڹؽ�����ϵ�´��ݸ�����Ŀ�����Ϣ
class CAxisControl:public CBaseControl
{
public:
	void sendAxisControlInstr(AXIS axis);
};
///�������ڲ���ָ��ʱ���Ϳ�����Ϣ
class CInstrControl:public CBaseControl
{
public:
	void sendInstrControlInstr(INSTR axis);
};
///����������ҵ�ļ���Ϣ�Ĵ���
class CJobControl:public CBaseControl
{
public:
	void sendJobControlInstr(std::string str);
};


