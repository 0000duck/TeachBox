/**
 *@file
 *文件名称：InstuctionHeader.h
 *
 *摘要：设置指令的文本格式
 *
 *@author fly1992@163.com
 *
 **/
#pragma once

#include "GlobalVar.h"
///宏定义要加载的XML文件名
#define INSTRMOVJ (_T("OrderMovj.xml"))
#define INSTRMOVL (_T("OrderMovl.xml"))
#define INSTRMOVC (_T("OrderMovc.xml"))
///指令格式类
class CStrInstuction
{
public:
	CStrInstuction(CStdString temp)
	{
		if (_tcscmp(temp, INSTRMOVJ) == 0 )
		{
			
			m_SzInstrType=_T("MOVJ ");
			m_SzInstrSpeedT=_T(" VJ = ");
		}
		else if (_tcscmp(temp, INSTRMOVL) == 0)
		{
			m_SzInstrType=_T("MOVL ");
			m_SzInstrSpeedT=_T(" V = ");
		}
		else if (_tcscmp(temp, INSTRMOVC) == 0)
		{
			m_SzInstrType=_T("MOVL ");
			m_SzInstrSpeedT=_T(" V = ");
		}
		m_SzInstrSpeedV=_T("10");
		m_SzInstrPLT=_T(" PL=");
		m_SzInstrPLV=_T("2");
		m_SzInstrOther=_T(" NWAIL UNTIL IN#(16)=ON");
		m_SzInstrAll=_T("");
		m_SzInstrDisplay=_T("");
	}
	~CStrInstuction(){}
	CStdString GetInstrAll()
	{
		m_SzInstrAll=m_SzInstrType+m_SzInstrPos+m_SzInstrSpeedT+m_SzInstrSpeedV+m_SzInstrPLT+m_SzInstrPLV+m_SzInstrOther;
		return m_SzInstrAll;
	}
	CStdString GetInstrDisplay()
	{
		m_SzInstrDisplay=m_SzInstrType+m_SzInstrPos+m_SzInstrSpeedT+m_SzInstrSpeedV;
		return m_SzInstrDisplay;
	}
	void SetInstrSpeedV(CStdString temp)
	{
		m_SzInstrSpeedV=temp;
	}
	void SetInstrPLV(CStdString temp)
	{
		m_SzInstrPLV=temp;
	}
	void SetInstrPos(CStdString temp)
	{
		m_SzInstrPos=temp;
	}
private:
	CStdString m_SzInstrType;
	CStdString m_SzInstrPos;
	CStdString m_SzInstrSpeedT;
	CStdString m_SzInstrSpeedV;
	CStdString m_SzInstrPLT;
	CStdString m_SzInstrPLV;
	CStdString m_SzInstrOther;
	CStdString m_SzInstrAll;
	CStdString m_SzInstrDisplay;
};