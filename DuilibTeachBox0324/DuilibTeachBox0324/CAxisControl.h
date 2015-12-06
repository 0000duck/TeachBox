/**
*@file
*文件名称：CAxisControl.h
*
*摘要：封装各个轴的控制信息，指令插入信息以及作业指令信息并发送
*
*@author fly1992@163.com
*
**/
#pragma  once
#include "GlobalVar.h"
#include "CCommunication.h"
#include "CRobotDataTypeFactory.h"
///适配器模式，封装了通讯类用于发送和接受字符
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
///此类用于关节坐标系下传递各个轴的控制信息
class CAxisControl:public CBaseControl
{
public:
	void sendAxisControlInstr(AXIS axis);
};
///此类用于插入指令时发送控制信息
class CInstrControl:public CBaseControl
{
public:
	void sendInstrControlInstr(INSTR axis);
};
///此类用于作业文件信息的传递
class CJobControl:public CBaseControl
{
public:
	void sendJobControlInstr(std::string str);
};


