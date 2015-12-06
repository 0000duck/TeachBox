/**
*@file
*文件名称：CFileButtonState.h
*
*摘要：作业文件编辑按钮处理
*
*@author fly1992@163.com
*
**/
#pragma once
#include "GlobalVar.h"
#include "Control.h"
typedef enum ButtonFlag{
	EMPTY,NEW,NEWOK,NEWCANCLE,
	INSERT,INSERTOK,INSERTOKOK,INSERTCANCLECANCLE,
	INSERTCANCLE,EXIT,BACK,OPEN,DELETEINSTR,SETPC,MODIFY,REMOVEFILE
};

struct buttonState{
	CStdString str;
	bool bl;
};
///作业文件按钮处理类
class CFileButtonState
{
public:
	static buttonState Init[];
	static buttonState bsInit[];
	static buttonState bsNewOk[];
	static buttonState bsNewOk1[];///<至少有一条指令时的状态
	static buttonState bsNewOk2[];//operator
	static buttonState bsNew[];
	static buttonState bsInsert[];
	static buttonState bsInsertOk[];
	static buttonState bsExit[];
	static buttonState bsInitPro[];
	static buttonState bsInitPro1[];//operator
	CFileButtonState(FileButtonControl* fbc);
	///设置按钮显示状态
	void SetFileButtonState(buttonState bs[]);
	///设置按钮状态标志
	void ChangeButtonState(CStdString stdStr);
	///处理状态响应
	void SwitchState(ButtonFlag bflag);
	///状态响应函数
	void newRespond();
	void newOkRespond();
	void newCancleRespond();
	void insertRespond();
	void insertOkRespond();
	void insertOkOKRespond();
	void insertCancleRespond();
	void insertCancleCancleRespond();
	void deleteInstrRespond();
	void removeFileRespond();
	void openRespond();
	void setPCRespond();
	void modifyRespond();
	void exitRespond();

private:
	std::string receiceStrAfterInsert(CStdString stdStr);
	FileButtonControl* m_pfileButtonControl;
	ButtonFlag m_bflag;
	ButtonFlag m_oldFlag;
	bool m_bmodifyFlag;
};
