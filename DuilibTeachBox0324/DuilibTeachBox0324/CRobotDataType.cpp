/**
 *@file
 *文件名称：CRobotDataType.cpp
 *
 *摘要：用于发送的机器人数据指令类型，例如关节数据，状态指令
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
 *函数名称：InstrData
 *函数功能：获取机器人指令对应的字符串
 *
 * @return string 机器人指令对应的字符串
 **/
std::string InstrData::GetRobotDataStr()
{
	
	return NumToString(m_motionInstruction.iMotionInstr);
}
/**
 *@file
 *函数名称：CRobotJointData
 *函数功能：获取机器人关节数据对应的字符串
 *
 * @return string 机器人关节数据对应的字符串
 **/
std::string CRobotJointData::GetRobotDataStr()
{
	return strInstr;
}
/**
 *@file
 *函数名称：CRobotXYZABCData
 *函数功能：获取机器人直角空间位置数据对应的字符串
 *
 * @return string 机器人直角空间位置数据对应的字符串
 **/
std::string CRobotXYZABCData::GetRobotDataStr()
{
	return "";
}