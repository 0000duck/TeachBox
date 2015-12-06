/**
 *@file
 *�ļ����ƣ�DisplayManager.cpp
 *ժҪ��led�Լ���������ʾ�豸�����ʵ��
 *@author fly1992@163.com
 **/
#pragma once
#include "DisplayManager.h"
///led�Լ�bee�����״ֵ̬���Կ���led�Լ�bee�Ŀ���
int CDisplayDev::disPlayDevValue=0;
/**
 *@file
 *�������ƣ�On
 *�������ܣ���ʾ�豸��
 * @param iValue ��״ֵ̬
 **/
void CDisplayDev::On(int iValue)
{
	disPlayDevValue |=iValue;
	SetOutputData1(disPlayDevValue);
}
/**
 *@file
 *�������ƣ�Off
 *�������ܣ���ʾ�豸�ر�
 * @param iValue ��״ֵ̬
 **/
void CDisplayDev::Off(int iValue)
{
	disPlayDevValue &=~iValue;
	SetOutputData1(disPlayDevValue);
}
/**
 *@file
 *�������ƣ�On
 *�������ܣ�bee�豸��
 * @param iValue ��״ֵ̬
 **/
void CDisplayBee::On(int iValue)
{
	CDisplayDev::On(iValue);
	Delayms(DELAYMS);
	CDisplayDev::Off(iValue);

}

///����led�Լ�bee����ʵ��
CDisplayDev* CDisplayDevManager::displayLed=new CDisplayDev();
CDisplayDev* CDisplayDevManager::displayBee=new CDisplayBee();



