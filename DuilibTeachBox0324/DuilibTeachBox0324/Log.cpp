#include "Log.h"

string CLog::szLogpath = "";

string CLog::GetLogFilePath()  
{  
	if (!szLogpath.empty()) return szLogpath;

	TCHAR tszModule[MAX_PATH + 1] = { 0 };
	string szPath;
	::GetModuleFileName(NULL, tszModule, MAX_PATH);
	CStdString sInstancePath = tszModule;
	int pos = sInstancePath.ReverseFind(_T('\\'));
	if( pos >= 0 ) sInstancePath = sInstancePath.Left(pos + 1);  
	szPath = Tchar2String(sInstancePath);

	SYSTEMTIME stUTC;  
	::GetSystemTime(&stUTC);  

	const int nBufSize = 256;  
	char chBuf[nBufSize];  

	sprintf(chBuf,"%u_%u_%u_%u_%u_%u",              
		  stUTC.wYear, stUTC.wMonth, stUTC.wDay,  
		  stUTC.wHour, stUTC.wMinute, stUTC.wSecond);

    szPath = szPath + "\\" + "Log_" + chBuf + ".txt";
	szLogpath = szPath;
	return szPath;
}  

void CLog::WriteLog(char* lpszFormat, ...) 
{  
	// 格式化我们得到的数据
	va_list args;
	va_start(args, lpszFormat);

	char szBuffer[512];
	_vsnprintf(szBuffer, 512, lpszFormat, args);

	string szPath;  
    szPath = GetLogFilePath();  

    ofstream fout(szPath.c_str(),ios::app);  
    fout.seekp(ios::end);

	fout << GetSystemTime() << szBuffer;  
    fout.close(); 

	va_end(args);
}  
    
string CLog::GetSystemTime()    
{    

	SYSTEMTIME stUTC;  
	::GetSystemTime(&stUTC);  

	const int nBufSize = 256;  
	TCHAR chBuf[nBufSize];  

	wsprintf(chBuf,_T("[UTC: %u/%u/%u %u:%u:%u:%u %d\r\n] "),              
		  stUTC.wYear, stUTC.wMonth, stUTC.wDay,  
		  stUTC.wHour, stUTC.wMinute, stUTC.wSecond,  
		  stUTC.wMilliseconds,stUTC.wDayOfWeek); 

	return Tchar2String(chBuf);
}