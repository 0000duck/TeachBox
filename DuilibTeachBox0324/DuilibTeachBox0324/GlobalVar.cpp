/**
*@file
*文件名称：GlobalVar.cpp
*摘要：定义全局变量
*@author fly1992@163.com
**/

#include "GlobalVar.h"

const wchar_t *HostIP=_T("223.3.50.100");///<主机（服务器）的ip地址
const int PORT=6000;///<通信端口号

KEYSWITCH GKW;///<区分到底是newfile还是project按键的退出

///用户级别定义
USERLIMITS USLM;

HWND h_newFileWnd=NULL;

/**
*@brief 宽字符转string
*函数名称：Tchar2String
*函数功能：宽字符转string
* @param LPCTSTR 宽字符
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
*@brief string转宽字符
*函数名称：StringToTChar
*函数功能：宽字符转string
* @param string char字符串
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
 *@brief 延时
 *函数名称：Delayms
 *函数功能：延时
 * @param TempTime 延时时间
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