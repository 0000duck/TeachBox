/**
 *@file
 *�ļ����ƣ�CRobotDataTypeFactory.cpp
 *
 *ժҪ��������ָ��������������������ָ����ָ�����ͣ���������ģʽ
 *
 *@author fly1992@163.com
 *
 **/
#include "CRobotDataTypeFactory.h"
///�����ŷ�״̬����
CRobotDataType* 
InstrDataFactory::pServeOnData=
new InstrData(MotionInstr(CRobotStateValue::SERVEON));

CRobotDataType* 
InstrDataFactory::pServeOffData=
new InstrData(MotionInstr(CRobotStateValue::SERVEOFF));
///�����ٶ�״̬����
CRobotDataType* 
InstrDataFactory::pSpeedLowData=
new InstrData(MotionInstr(CRobotStateValue::SPEEDLOW));

CRobotDataType* 
InstrDataFactory::pSpeedMidData=
new InstrData(MotionInstr(CRobotStateValue::SPEEDMID));

CRobotDataType* 
InstrDataFactory::pSpeedHighData=
new InstrData(MotionInstr(CRobotStateValue::SPEEDHIGH));
///��������״̬����
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
///������ͬ��״̬����
CRobotDataType* 
InstrDataFactory::pSyncData=
new InstrData(MotionInstr(CRobotStateValue::SYNC));

CRobotDataType* 
InstrDataFactory::pUnsyncData=
new InstrData(MotionInstr(CRobotStateValue::UNSYNC));
///�����˶���״̬
CRobotDataType* 
InstrDataFactory::pRobotBaseData=
new InstrData(MotionInstr(CRobotStateValue::ROBOTBASE));

CRobotDataType* 
InstrDataFactory::pRobotPosData=
new InstrData(MotionInstr(CRobotStateValue::POSTIONER));
///������ģʽ״̬
CRobotDataType* 
InstrDataFactory::pModelTeachData=
new InstrData(MotionInstr(CRobotStateValue::MODELTEACH));

CRobotDataType* 
InstrDataFactory::pModelReplayData=
new InstrData(MotionInstr(CRobotStateValue::MODELREPALY));

///�����ָ��
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

