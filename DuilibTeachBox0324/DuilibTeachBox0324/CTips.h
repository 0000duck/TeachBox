/**
 *@file
 *�ļ����ƣ�CTips.h
 *
 *ժҪ��ʾ����Ϣ��ʾ,��Ϊ������Ϣ��������Ϣ����ʾ��Ϣ��
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
///������Ϣ��ʾ����ʾ��Ϣ֮ǰ���������ո�ʹ����ʾͼ�겻����ס
typedef enum ERRORTYPE{ERRORINFO,ALARMINFO,TIPSINFO};
static const CStdString ErrorInfoImage[]={
	_T("ErrorIconNew1.png"),
	_T("TipsIconNew1.png"),
	_T("TipsIconNew1.png")
};

///static �ؼ��ֿ���ʹ�ö���Ķ���������ڱ��ļ��ɼ�����ֹobj�ļ��ϲ�ʱ���ض���
///������ʾ����Ϣ
static const struct ErrorInfo{
	CStdString errorStr;
	ERRORTYPE errorType; 
}errorTable[]={
	_T("      ����Ա��¼�ɹ�"),TIPSINFO,
	_T("      ����Ա��¼�ɹ�"),TIPSINFO,
	_T("      ����ŷ�"),TIPSINFO,
	_T("      �ŷ��ѿ�ͨ"),TIPSINFO,
	_T("      �ŷ�û��"),ERRORINFO,
	_T("      �����ŷ��ϵ磬�����˳�"),ERRORINFO,
	_T("      ����"),TIPSINFO,
	_T("      ����"),TIPSINFO,
	_T("      ����"),TIPSINFO,
	_T("      ֱ������"),TIPSINFO,
	_T("      �ؽ�����"),TIPSINFO,
	_T("      ���л����ؽ�����ϵ��"),ERRORINFO,
	_T("      ��������"),TIPSINFO,
	_T("      �û�����"),TIPSINFO,
	_T("      ͬ��"),TIPSINFO,
	_T("      ��ͬ��"),TIPSINFO,
	_T("      ��ͬ��״̬����ť��Ч��"),ERRORINFO,
	_T("       ���л���ͬ��״̬"),ERRORINFO,
	_T("      ������1"),TIPSINFO,
	_T("      ��λ��"),TIPSINFO,
	_T("      ʾ��ģʽ"),TIPSINFO,
	_T("      ����ģʽ"),TIPSINFO,
	_T("      ���������λ��,����P000"),ERRORINFO,
	_T("      ����������ٶ�1-100"),ERRORINFO,
	_T("      ���������PL,1-8"),ERRORINFO,
	_T("      ����������ļ���,��ĸ��ͷ��10���ַ�����"),ERRORINFO,
	_T("      ��Ч����"),TIPSINFO

};
///������ʾ��Ϣ������
typedef enum ERRORMSGINDEX{
								OPERATOR_LOGIN_SUCCESS=0,//in case overflow of array
								ADMIN_LOGIN_SUCCESS,
								PLEASE_OPEN_SERVE,
								SERVE_OPENED,
								SERVE_NOT_OPEN,
								PLEASE_SERVE_OFF,
								HIGH_SPEED,
								MID_SPEED,
								LOW_SPEED,
								CART_COORD,
								JOINT_COORD,
								PLEASE_SWITCH_JOINT_COORD,
								TOOL_COORD,
								USER_COORD,
								SYNC_MODEL,
								UNSYNC_MODEL,
								NOT_SYNC_MODEL,
								PLEASE_SYNC_MODEL,
								ROBOT_BASE,
								ROBOT_POSITIONER,
								MODEL_TEACH,
								MODEL_REPALY,
								INVALID_POSTION,
								INVALID_SPEED,
								INVALID_PL,
								INVALID_FILENAME,
								VALID_INPUT
						  };
/**
 *@brief �������ɲ�ͬ�������͵���ʾ��Ϣ
 *�����ƣ�CTipsElementProduct
 *�๦�ܣ��������ɲ�ͬ�������͵���ʾ��Ϣ
 **/
class CTipsElementProduct
{
public:
	virtual CListLabelElementUI* CreateTipsElement(ERRORMSGINDEX errorIndex)=0;
protected:
	CListLabelElementUI* CreateTips(ERRORMSGINDEX errorIndex,CStdString strImage);
};

class CTipsInfoProduct:public CTipsElementProduct
{
public:
	CListLabelElementUI* CreateTipsElement(ERRORMSGINDEX errorIndex);
};

class CAlarmInfoProduct:public CTipsElementProduct
{
public:
	CListLabelElementUI* CreateTipsElement(ERRORMSGINDEX errorIndex);
};

class CErrorInfoProduct:public CTipsElementProduct
{
public:
	CListLabelElementUI* CreateTipsElement(ERRORMSGINDEX errorIndex);
};
/**
 *@brief �����Ͽ���Ϣ��ʾ
 *�����ƣ�CTips
 *�๦�ܣ������Ͽ���Ϣ��ʾ
 **/
class CTips
{
public:
	
	void CurrentTipsDisplay();
	void AddTips(CTipsElementProduct &tipsProduct,ERRORMSGINDEX errorIndex);
	ERRORTYPE GetErrorType();
	static CTips* GetInstance(CComboUI* pCombo);
public:
	static CTipsInfoProduct tipsInfoProduct;
	static CAlarmInfoProduct alarmInfoProduct;
	static CErrorInfoProduct errorInfoProduct;
private:
	CTips(CComboUI* pCombo);
	static CTips* tips;
	CComboUI* m_pCombo;
	CListLabelElementUI* m_pCurrentListLableElement;
	ERRORTYPE m_correntErrorType;
};




