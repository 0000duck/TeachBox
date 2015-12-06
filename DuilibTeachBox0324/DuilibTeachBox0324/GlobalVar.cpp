/**
*@file
*�ļ����ƣ�GlobalVar.cpp
*ժҪ������ȫ�ֱ���
*@author fly1992@163.com
**/

#include "GlobalVar.h"

const wchar_t *HostIP=_T("223.3.50.100");///<����������������ip��ַ
const int PORT=6000;///<ͨ�Ŷ˿ں�

KEYSWITCH GKW;///<���ֵ�����newfile����project�������˳�

///�û�������
USERLIMITS USLM;

HWND h_newFileWnd=NULL;

/**
*@brief ���ַ�תstring
*�������ƣ�Tchar2String
*�������ܣ����ַ�תstring
* @param LPCTSTR ���ַ�
**/
std::string Tchar2String(LPCTSTR tChar)
{
	int iLen = WideCharToMultiByte(CP_ACP, 0,tChar, -1, NULL, 0, NULL, NULL);
	char* chRtn =new char[iLen*sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, tChar, -1, chRtn, iLen, NULL, NULL);
	std::string str(chRtn);
	return str;
}
/**
*@brief stringת���ַ�
*�������ƣ�StringToTChar
*�������ܣ����ַ�תstring
* @param string char�ַ���
**/
CStdString StringToTChar(std::string str)
{
	TCHAR *szBuf= new TCHAR[MAX_PATH];
	::ZeroMemory(szBuf, (MAX_PATH) * sizeof(TCHAR));
	int iLen = str.length();
	LPWSTR lpText = new WCHAR[iLen + 1];
	::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (LPWSTR)lpText, iLen) ;
	_stprintf(szBuf, lpText);
	delete[] lpText;
	CStdString wStr=szBuf;
	delete[] szBuf;//delelte memory
	return wStr;
}

/**
 *@brief ��ʱ
 *�������ƣ�Delayms
 *�������ܣ���ʱ
 * @param TempTime ��ʱʱ��
 **/
void Delayms(DWORD TempTime)
{
	DWORD start;
	DWORD time_i=0;
	start=GetTickCount();
	while(time_i<=TempTime)
	{
		time_i=GetTickCount()-start;
	}
}