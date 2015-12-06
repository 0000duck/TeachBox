/**
 *@file
 *�ļ����ƣ�CTips.cpp
 *ժҪ��ʾ����Ϣ��ʾ,��Ϊ������Ϣ��������Ϣ����ʾ��Ϣ��
 *@author fly1992@163.com
 **/
#pragma once
#include "CTips.h"
CTips* CTips::tips=NULL;
CTipsInfoProduct CTips::tipsInfoProduct;
CAlarmInfoProduct CTips::alarmInfoProduct;
CErrorInfoProduct CTips::errorInfoProduct;
/**
 *@brief ��ȡtips���
 *�������ƣ�GetInstance
 *�������ܣ���ȡtips���
 * @param CComboUI*��Ͽ�ָ��
 * @return CTips* ��Ͽ���Ϣ��ʾ��ָ��
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
 *@brief ���캯��
 *�������ƣ�CTips
 *�������ܣ����캯��
 * @param CComboUI* 
 **/
CTips::CTips(CComboUI* pCombo)
{
	m_pCombo=pCombo;
	m_pCurrentListLableElement=NULL;
}
/**
 *@brief ��Ӳ�ͬ���͵���Ϣ��ʾ����Ͽ���б����
 *�������ƣ�AddTips
 *�������ܣ���Ӳ�ͬ���͵���Ϣ��ʾ����Ͽ���б����
 * @param CTipsElementProduct &������Ҫ��ӵ���Ϣ��ʾ����
 * @param ERRORMSGINDEX �������� 
 **/
void CTips::AddTips(CTipsElementProduct &tipsProduct,ERRORMSGINDEX errorIndex)
{
	m_pCurrentListLableElement=tipsProduct.CreateTipsElement(errorIndex);
	m_pCombo->AddAt(m_pCurrentListLableElement,0);
	m_correntErrorType=errorTable[errorIndex].errorType;
}
/**
 *@brief ��ȡ��ǰ��ʾ�Ĵ�������
 *�������ƣ�GetErrorType
 *�������ܣ���ȡ��ǰ��ʾ�Ĵ�������
 * @return ERRORTYPE ��������
 **/
ERRORTYPE CTips::GetErrorType()
{
	return m_correntErrorType;
}
/**
 *@brief ��ʾ��ǰ��Ϣ
 *�������ƣ�CurrentTipsDisplay
 *�������ܣ���ʾ��ǰ��Ϣ
 **/
void CTips::CurrentTipsDisplay()
{
	m_pCombo->SelectItem(0);
	m_pCombo->SetBkImage(ErrorInfoImage[m_correntErrorType]);
}
/**
 *@brief ����Ҫ�����ʾ��Ϣ����
 *�������ƣ�CTipsElementProduct
 *�������ܣ�����Ҫ�����ʾ��Ϣ����
 * @param ERRORMSGINDEX ��������  
 * @param CStdString ��Ϣ��ʾ���� 
 * @return CListLabelElementUI* ��ʾ��Ϣ����
 **/
CListLabelElementUI* CTipsElementProduct::CreateTips(ERRORMSGINDEX errorIndex,CStdString strImage)
{
	CListLabelElementUI* listElement=new CListLabelElementUI;
	listElement->SetText(errorTable[errorIndex].errorStr);
	listElement->SetBkImage(strImage);
	return listElement;
}
///������ʾ��Ϣ����
CListLabelElementUI* CTipsInfoProduct::CreateTipsElement(ERRORMSGINDEX errorIndex)
{
	return CreateTips(errorIndex,_T("TipsIconNew.png"));
}
///����������Ϣ����
CListLabelElementUI* CAlarmInfoProduct::CreateTipsElement(ERRORMSGINDEX errorIndex)
{
	return CreateTips(errorIndex,_T("TipsIconNew.png"));
}
///����������Ϣ����
CListLabelElementUI* CErrorInfoProduct::CreateTipsElement(ERRORMSGINDEX errorIndex)
{
	return CreateTips(errorIndex,_T("ErrorIconNew.png"));
}
