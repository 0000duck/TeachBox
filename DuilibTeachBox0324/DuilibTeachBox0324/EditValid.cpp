/**
*@file
*�ļ����ƣ�EditValid.cpp
*
*ժҪ��������ϢУ�飬�ж��Ƿ����
*
*@author fly1992@163.com
*
**/
#include "EditValid.h"
CRegexpT <char> EditValid::regexRobotPos("^P[0-9]{3}$");
CRegexpT <char> EditValid::regexFileName("^[a-zA-Z][0-9a-zA-Z]{0,8}[0-9a-zA-Z]$");
CRegexpT <char> EditValid::regexSpeed("^[1-9][0-9]{0,2}$");
CRegexpT <char> EditValid::regexPL("^[0-9]$");