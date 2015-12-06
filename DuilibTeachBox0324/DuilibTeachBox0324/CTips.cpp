/**
 *@file
 *文件名称：CTips.cpp
 *摘要：示教信息提示,分为错误信息、警告信息、提示信息等
 *@author fly1992@163.com
 **/
#pragma once
#include "CTips.h"
CTips* CTips::tips=NULL;
CTipsInfoProduct CTips::tipsInfoProduct;
CAlarmInfoProduct CTips::alarmInfoProduct;
CErrorInfoProduct CTips::errorInfoProduct;
/**
 *@brief 获取tips句柄
 *函数名称：GetInstance
 *函数功能：获取tips句柄
 * @param CComboUI*组合框指针
 * @return CTips* 组合框信息提示类指针
 **/
CTips* CTips::GetInstance(CComboUI* pCombo)
{
	if (tips==NULL)
	{
		tips=new CTips(pCombo);
	}
	return tips;
}
/**
 *@brief 构造函数
 *函数名称：CTips
 *函数功能：构造函数
 * @param CComboUI* 
 **/
CTips::CTips(CComboUI* pCombo)
{
	m_pCombo=pCombo;
	m_pCurrentListLableElement=NULL;
}
/**
 *@brief 添加不同类型的信息提示到组合框的列表框中
 *函数名称：AddTips
 *函数功能：添加不同类型的信息提示到组合框的列表框中
 * @param CTipsElementProduct &创建需要添加的信息提示类型
 * @param ERRORMSGINDEX 错误索引 
 **/
void CTips::AddTips(CTipsElementProduct &tipsProduct,ERRORMSGINDEX errorIndex)
{
	m_pCurrentListLableElement=tipsProduct.CreateTipsElement(errorIndex);
	m_pCombo->AddAt(m_pCurrentListLableElement,0);
	m_correntErrorType=errorTable[errorIndex].errorType;
}
/**
 *@brief 获取当前显示的错误类型
 *函数名称：GetErrorType
 *函数功能：获取当前显示的错误类型
 * @return ERRORTYPE 错误类型
 **/
ERRORTYPE CTips::GetErrorType()
{
	return m_correntErrorType;
}
/**
 *@brief 显示当前信息
 *函数名称：CurrentTipsDisplay
 *函数功能：显示当前信息
 **/
void CTips::CurrentTipsDisplay()
{
	m_pCombo->SelectItem(0);
	m_pCombo->SetBkImage(ErrorInfoImage[m_correntErrorType]);
}
/**
 *@brief 创建要添加提示信息对象
 *函数名称：CTipsElementProduct
 *函数功能：创建要添加提示信息对象
 * @param ERRORMSGINDEX 错误索引  
 * @param CStdString 信息提示内容 
 * @return CListLabelElementUI* 提示信息对象
 **/
CListLabelElementUI* CTipsElementProduct::CreateTips(ERRORMSGINDEX errorIndex,CStdString strImage)
{
	CListLabelElementUI* listElement=new CListLabelElementUI;
	listElement->SetText(errorTable[errorIndex].errorStr);
	listElement->SetBkImage(strImage);
	return listElement;
}
///创建提示信息对象
CListLabelElementUI* CTipsInfoProduct::CreateTipsElement(ERRORMSGINDEX errorIndex)
{
	return CreateTips(errorIndex,_T("TipsIconNew.png"));
}
///创建警告信息对象
CListLabelElementUI* CAlarmInfoProduct::CreateTipsElement(ERRORMSGINDEX errorIndex)
{
	return CreateTips(errorIndex,_T("TipsIconNew.png"));
}
///创建错误信息对象
CListLabelElementUI* CErrorInfoProduct::CreateTipsElement(ERRORMSGINDEX errorIndex)
{
	return CreateTips(errorIndex,_T("ErrorIconNew.png"));
}
