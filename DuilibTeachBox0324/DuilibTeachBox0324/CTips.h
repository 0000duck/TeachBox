/**
 *@file
 *文件名称：CTips.h
 *
 *摘要：示教信息提示,分为错误信息、警告信息、提示信息等
 *
 *@author fly1992@163.com
 *
 **/
#pragma once
#include "GlobalVar.h"
///错误信息提示，提示信息之前加上六个空格，使得提示图标不被遮住
typedef enum ERRORTYPE{ERRORINFO,ALARMINFO,TIPSINFO};
static const CStdString ErrorInfoImage[]={
	_T("ErrorIconNew1.png"),
	_T("TipsIconNew1.png"),
	_T("TipsIconNew1.png")
};

///static 关键字可以使得定义的对象仅仅限于本文件可见，防止obj文件合并时的重定义
///错误提示表信息
static const struct ErrorInfo{
	CStdString errorStr;
	ERRORTYPE errorType; 
}errorTable[]={
	_T("      操作员登录成功"),TIPSINFO,
	_T("      管理员登录成功"),TIPSINFO,
	_T("      请打开伺服"),TIPSINFO,
	_T("      伺服已开通"),TIPSINFO,
	_T("      伺服没开"),ERRORINFO,
	_T("      请先伺服断电，才能退出"),ERRORINFO,
	_T("      高速"),TIPSINFO,
	_T("      中速"),TIPSINFO,
	_T("      低速"),TIPSINFO,
	_T("      直角坐标"),TIPSINFO,
	_T("      关节坐标"),TIPSINFO,
	_T("      请切换到关节坐标系！"),ERRORINFO,
	_T("      工具坐标"),TIPSINFO,
	_T("      用户坐标"),TIPSINFO,
	_T("      同步"),TIPSINFO,
	_T("      非同步"),TIPSINFO,
	_T("      非同步状态，按钮无效！"),ERRORINFO,
	_T("       请切换到同步状态"),ERRORINFO,
	_T("      机器人1"),TIPSINFO,
	_T("      变位机"),TIPSINFO,
	_T("      示教模式"),TIPSINFO,
	_T("      再现模式"),TIPSINFO,
	_T("      请输入合理位置,例如P000"),ERRORINFO,
	_T("      请输入合理速度1-100"),ERRORINFO,
	_T("      请输入合理PL,1-8"),ERRORINFO,
	_T("      请输入合理文件名,字母开头的10个字符以内"),ERRORINFO,
	_T("      有效输入"),TIPSINFO

};
///错误提示信息表索引
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
 *@brief 用于生成不同错误类型的提示信息
 *类名称：CTipsElementProduct
 *类功能：用于生成不同错误类型的提示信息
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
 *@brief 完成组合框信息提示
 *类名称：CTips
 *类功能：完成组合框信息提示
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




