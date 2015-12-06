/**
 *@file
 *文件名称：DisplayManager.cpp
 *摘要：led以及蜂鸣器显示设备的输出实现
 *@author fly1992@163.com
 **/
#pragma once
#include "DisplayManager.h"
///led以及bee的输出状态值，以控制led以及bee的开关
int CDisplayDev::disPlayDevValue=0;
/**
 *@file
 *函数名称：On
 *函数功能：显示设备打开
 * @param iValue 开状态值
 **/
void CDisplayDev::On(int iValue)
{
	disPlayDevValue |=iValue;
	SetOutputData1(disPlayDevValue);
}
/**
 *@file
 *函数名称：Off
 *函数功能：显示设备关闭
 * @param iValue 开状态值
 **/
void CDisplayDev::Off(int iValue)
{
	disPlayDevValue &=~iValue;
	SetOutputData1(disPlayDevValue);
}
/**
 *@file
 *函数名称：On
 *函数功能：bee设备打开
 * @param iValue 开状态值
 **/
void CDisplayBee::On(int iValue)
{
	CDisplayDev::On(iValue);
	Delayms(DELAYMS);
	CDisplayDev::Off(iValue);

}

///生成led以及bee对象实例
CDisplayDev* CDisplayDevManager::displayLed=new CDisplayDev();
CDisplayDev* CDisplayDevManager::displayBee=new CDisplayBee();



