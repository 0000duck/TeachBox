/**
 *@file
 *�ļ����ƣ�CRobotDataType.cpp
 *
 *ժҪ�����ڷ��͵Ļ���������ָ�����ͣ�����ؽ����ݣ�״ָ̬��
 *
 *@author fly1992@163.com
 **/
#include "CRobotDataType.h"
InstrData::InstrData(MotionInstr mi):
							m_motionInstruction(mi)
{
	
}
/**
 *@file
 *�������ƣ�InstrData
 *�������ܣ���ȡ������ָ���Ӧ���ַ���
 *
 * @return string ������ָ���Ӧ���ַ���
 **/
std::string InstrData::GetRobotDataStr()
{
	
	return NumToString(m_motionInstruction.iMotionInstr);
}
/**
 *@file
 *�������ƣ�CRobotJointData
 *�������ܣ���ȡ�����˹ؽ����ݶ�Ӧ���ַ���
 *
 * @return string �����˹ؽ����ݶ�Ӧ���ַ���
 **/
std::string CRobotJointData::GetRobotDataStr()
{
	return strInstr;
}
/**
 *@file
 *�������ƣ�CRobotXYZABCData
 *�������ܣ���ȡ������ֱ�ǿռ�λ�����ݶ�Ӧ���ַ���
 *
 * @return string ������ֱ�ǿռ�λ�����ݶ�Ӧ���ַ���
 **/
std::string CRobotXYZABCData::GetRobotDataStr()
{
	return "";
}