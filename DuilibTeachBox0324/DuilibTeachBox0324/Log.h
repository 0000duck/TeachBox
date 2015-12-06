#pragma once
#include "GlobalVar.h"
#include <fstream>    

//log文件路径  
#define LOG_FILE_NAME "log.txt"  
  
//启用开关  
#define LOG_ENABLE  

class CLog    
{    
public:	
    static string GetLogFilePath();
	static void WriteLog(char* lpszFormat, ...);
private: 	
	static string szLogpath;
    static string GetSystemTime();
};
  
#ifdef LOG_ENABLE  
  
//用下面这些宏来使用本文件
//C99
#define LOG(format,...)              CLog::WriteLog(format,__VA_ARGS__);
//GCC
//#define LOG(format,args...)        CLog::WriteLog(format,##args);
#define LOG_FILE        LOG("File : %s\n",__FILE__)
#define LOG_FUNC        LOG("Func : %s\n",__FUNCTION__)
#define LOG_LINE        LOG("Line : %d\n",__LINE__)
#define LOG_FUNC_BEGIN  LOG("--------------------%s  Begin------------------ \n",__FUNCTION__);
#define LOG_FUNC_END    LOG("--------------------%s  End-------------------- \n",__FUNCTION__);
  
#else  
  
#define LOG_FILE
#define LOG_FUNC
#define LOG_LINE
#define LOG_FUNC_BEGIN
#define LOG_FUNC_END
  
#endif  