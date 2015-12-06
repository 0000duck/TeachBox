/**
 *@file
 *�ļ����ƣ�CRobotDataType.h
 *
 *ժҪ�����ڷ��͵Ļ���������ָ�����ͣ�����ؽ����ݣ�״ָ̬��
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

///�����˸���ָ��������
class CRobotDataType
{
public:
	virtual std::string GetRobotDataStr()=0;
};
///�����˿�������������
class InstrData:public CRobotDataType
{
public:
	explicit InstrData(MotionInstr mi);
	std::string GetRobotDataStr();
							
private:
	MotionInstr m_motionInstruction;
};
///�����˹ؽڿռ�������
class CRobotJointData:public CRobotDataType
{
public:
	CRobotJointData(std::string str):strInstr(str){}
	std::string GetRobotDataStr();
private:
	std::string strInstr;
};
///������ֱ�ǿռ�������
class CRobotXYZABCData:public CRobotDataType
{
public:
	std::string GetRobotDataStr();
};



