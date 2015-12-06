/**
*@file
*�ļ����ƣ�CFileButtonState.h
*
*ժҪ����ҵ�ļ��༭��ť����
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
///��ҵ�ļ���ť������
class CFileButtonState
{
public:
	static buttonState Init[];
	static buttonState bsInit[];
	static buttonState bsNewOk[];
	static buttonState bsNewOk1[];///<������һ��ָ��ʱ��״̬
	static buttonState bsNewOk2[];//operator
	static buttonState bsNew[];
	static buttonState bsInsert[];
	static buttonState bsInsertOk[];
	static buttonState bsExit[];
	static buttonState bsInitPro[];
	static buttonState bsInitPro1[];//operator
	CFileButtonState(FileButtonControl* fbc);
	///���ð�ť��ʾ״̬
	void SetFileButtonState(buttonState bs[]);
	///���ð�ť״̬��־
	void ChangeButtonState(CStdString stdStr);
	///����״̬��Ӧ
	void SwitchState(ButtonFlag bflag);
	///״̬��Ӧ����
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
