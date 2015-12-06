/**
 *@file
 *文件名称：CRobotDataTypeFactory.cpp
 *
 *摘要：机器人指令类型生产工厂，生产指定的指令类型，工厂方法模式
 *
 *@author fly1992@163.com
 *
 **/
#include "CRobotDataTypeFactory.h"
///生成伺服状态数据
CRobotDataType* 
InstrDataFactory::pServeOnData=
new InstrData(MotionInstr(CRobotStateValue::SERVEON));

CRobotDataType* 
InstrDataFactory::pServeOffData=
new InstrData(MotionInstr(CRobotStateValue::SERVEOFF));
///生成速度状态数据
CRobotDataType* 
InstrDataFactory::pSpeedLowData=
new InstrData(MotionInstr(CRobotStateValue::SPEEDLOW));

CRobotDataType* 
InstrDataFactory::pSpeedMidData=
new InstrData(MotionInstr(CRobotStateValue::SPEEDMID));

CRobotDataType* 
InstrDataFactory::pSpeedHighData=
new InstrData(MotionInstr(CRobotStateValue::SPEEDHIGH));
///生成坐标状态数据
CRobotDataType* 
InstrDataFactory::pCoordCartData=
new InstrData(MotionInstr(CRobotStateValue::COORDCART));

CRobotDataType* 
InstrDataFactory::pCoordJointData=
new InstrData(MotionInstr(CRobotStateValue::COORDJOINT));

CRobotDataType* 
InstrDataFactory::pCoordUserData=
new InstrData(MotionInstr(CRobotStateValue::COORDUSER));

CRobotDataType* 
InstrDataFactory::pCoordToolData=
new InstrData(MotionInstr(CRobotStateValue::COORDTOOL));
///机器人同步状态数据
CRobotDataType* 
InstrDataFactory::pSyncData=
new InstrData(MotionInstr(CRobotStateValue::SYNC));

CRobotDataType* 
InstrDataFactory::pUnsyncData=
new InstrData(MotionInstr(CRobotStateValue::UNSYNC));
///机器人对象状态
CRobotDataType* 
InstrDataFactory::pRobotBaseData=
new InstrData(MotionInstr(CRobotStateValue::ROBOTBASE));

CRobotDataType* 
InstrDataFactory::pRobotPosData=
new InstrData(MotionInstr(CRobotStateValue::POSTIONER));
///机器人模式状态
CRobotDataType* 
InstrDataFactory::pModelTeachData=
new InstrData(MotionInstr(CRobotStateValue::MODELTEACH));

CRobotDataType* 
InstrDataFactory::pModelReplayData=
new InstrData(MotionInstr(CRobotStateValue::MODELREPALY));

///轴控制指令
CRobotDataType *InstrDataFactory::axisInstr[]={
			new InstrData(MotionInstr(CRobotStateValue::AXISSM)),
			new InstrData(MotionInstr(CRobotStateValue::AXISSP)),
			new InstrData(MotionInstr(CRobotStateValue::AXISLM)),
			new InstrData(MotionInstr(CRobotStateValue::AXISLP)),
			new InstrData(MotionInstr(CRobotStateValue::AXISUM)),
			new InstrData(MotionInstr(CRobotStateValue::AXISUP)),
			new InstrData(MotionInstr(CRobotStateValue::AXISRM)),
			new InstrData(MotionInstr(CRobotStateValue::AXISRP)),
			new InstrData(MotionInstr(CRobotStateValue::AXISBM)),
			new InstrData(MotionInstr(CRobotStateValue::AXISBP)),
			new InstrData(MotionInstr(CRobotStateValue::AXISTM)),
			new InstrData(MotionInstr(CRobotStateValue::AXISTP)),
			new InstrData(MotionInstr(CRobotStateValue::AXISSTOP))
};

CRobotDataType *InstrDataFactory::insertInstr[]={
	new InstrData(MotionInstr(CRobotStateValue::INSERTMOVJ)),
	new InstrData(MotionInstr(CRobotStateValue::INSERTMOVL)),
	new InstrData(MotionInstr(CRobotStateValue::INSERTMOVC)),
	new InstrData(MotionInstr(CRobotStateValue::INSTREND))
};
///END

CRobotDataType* CRobotJointDataFactory::GetRobotDataType()
{
	return new CRobotJointData("");
}

CRobotDataType* CRobotXYZABCDataFactory::GetRobotDataType()
{
	return new CRobotXYZABCData;
}

