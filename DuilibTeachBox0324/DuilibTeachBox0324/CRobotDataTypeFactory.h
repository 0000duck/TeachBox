/**
 *@file
 *�ļ����ƣ�CRobotDataTypeFactory.h
 *
 *ժҪ��������ָ��������������������ָ����ָ�����ͣ���������ģʽ
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
#include "CRobotDataType.h"

///���ڲ�������״ָ̬�������ȡ����CRobotDataType
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