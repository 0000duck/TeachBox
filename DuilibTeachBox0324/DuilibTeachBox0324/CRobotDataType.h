/**
 *@file
 *文件名称：CRobotDataType.h
 *
 *摘要：用于发送的机器人数据指令类型，例如关节数据，状态指令
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include <string>
#include "GlobalVar.h"
struct MotionInstr 
{
	int iMotionInstr;
	explicit MotionInstr(int i):iMotionInstr(i){}
};

///机器人各种指令数据类
class CRobotDataType
{
public:
	virtual std::string GetRobotDataStr()=0;
};
///机器人控制命令数据类
class InstrData:public CRobotDataType
{
public:
	explicit InstrData(MotionInstr mi);
	std::string GetRobotDataStr();
							
private:
	MotionInstr m_motionInstruction;
};
///机器人关节空间数据类
class CRobotJointData:public CRobotDataType
{
public:
	CRobotJointData(std::string str):strInstr(str){}
	std::string GetRobotDataStr();
private:
	std::string strInstr;
};
///机器人直角空间数据类
class CRobotXYZABCData:public CRobotDataType
{
public:
	std::string GetRobotDataStr();
};



