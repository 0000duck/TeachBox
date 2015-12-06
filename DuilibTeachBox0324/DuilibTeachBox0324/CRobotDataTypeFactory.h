/**
 *@file
 *文件名称：CRobotDataTypeFactory.h
 *
 *摘要：机器人指令类型生产工厂，生产指定的指令类型，工厂方法模式
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CRobotDataType.h"

///用于产生常用状态指令，其类型取决于CRobotDataType
class InstrDataFactory
{
public:
	static CRobotDataType* pServeOnData;
	static CRobotDataType* pServeOffData;
	static CRobotDataType* pSpeedLowData;
	static CRobotDataType* pSpeedMidData;
	static CRobotDataType* pSpeedHighData;
	static CRobotDataType* pCoordCartData;
	static CRobotDataType* pCoordJointData;
	static CRobotDataType* pCoordToolData;
	static CRobotDataType* pCoordUserData;
	static CRobotDataType* pSyncData;
	static CRobotDataType* pUnsyncData;
	static CRobotDataType* pModelTeachData;
	static CRobotDataType* pModelReplayData;
	static CRobotDataType* pRobotBaseData;
	static CRobotDataType* pRobotPosData;
	static CRobotDataType *axisInstr[];
	static CRobotDataType *insertInstr[];
};

class CRobotDataTypeFactory
{
public:
	virtual CRobotDataType* GetRobotDataType()=0;
};

class CRobotJointDataFactory:public CRobotDataTypeFactory
{
public:
	CRobotDataType* GetRobotDataType();
};

class CRobotXYZABCDataFactory:public CRobotDataTypeFactory
{
public:
	CRobotDataType* GetRobotDataType();
};