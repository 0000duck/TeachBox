/**
*@file
*文件名称：CAxisControl.cpp
*
*摘要：封装各个轴的控制信息，指令插入信息以及作业指令信息并发送
*
*@author fly1992@163.com
*
**/
#include "CAxisControl.h"
/**
*@brief    发送控制信息命令
*函数名称：sendBaseControlInstr
*函数功能：根据不同的数据类型，发送不同的控制信息
*@param CRobotDataType*指定命令类型
**/
void CBaseControl::sendBaseControlInstr(CRobotDataType* p)
{
	pCommu->SendData(p);
}
/**
*@brief    接受控制信息命令
*函数名称：receiveControlInstr
*函数功能：接受控制信息命令
**/
std::string CBaseControl::receiveControlInstr()
{
	return pCommu->ReceiverData();
}
/**
*@brief    发送轴控制信息命令
*函数名称：sendAxisControlInstr
*函数功能：根据不同轴，发送不同的控制信息
*@param AXIS指定轴
**/
void CAxisControl::sendAxisControlInstr(AXIS axis)
{
	CRobotDataType* p=InstrDataFactory::axisInstr[axis];
	sendBaseControlInstr(p);
}
/**
*@brief    发送插入指令时的控制信息
*函数名称：sendInstrControlInstr
*函数功能：根据不同插入指令，发送不同的控制信息
*@param INSTR插入指令类型
**/
void CInstrControl::sendInstrControlInstr(INSTR axis)
{
	CRobotDataType* p=InstrDataFactory::insertInstr[axis];
	sendBaseControlInstr(p);
}
/**
*@brief    发送作业控制信息命令
*函数名称：sendJobControlInstr
*函数功能：根据不同作业语句，发送不同的控制信息
*@param str作业语句字符串
**/
void CJobControl::sendJobControlInstr(std::string str)
{
	CRobotDataType* p=new CRobotJointData(str);
	sendBaseControlInstr(p);
	Delayms(10);
	delete p;
}

