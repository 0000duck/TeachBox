/**
*@file
*�ļ����ƣ�EditValid.h
*
*ժҪ��������ϢУ�飬�ж��Ƿ����
*
*@author fly1992@163.com
*
**/
#pragma once
#include "deelx.h"
#include <string>
class EditValid
{
public:
	///�жϻ�����λ����Ϣ�Ƿ����
	bool isValidRobotPos(std::string str)
	{
		result=regexRobotPos.MatchExact(str.c_str());
		return  result.IsMatched();
	}
	///�жϻ�������ҵ�ļ�����Ϣ�Ƿ����
	bool isValidFileName(std::string str)
	{
		result=regexFileName.MatchExact(str.c_str());
		return  result.IsMatched();
	}
	///�жϻ������ٶ���Ϣ�Ƿ����
	bool isValidSpeed(std::string str)
	{
		result=regexSpeed.MatchExact(str.c_str());
		return  result.IsMatched();
	}
	///�жϻ�����PL��Ϣ�Ƿ����
	bool isValidPL(std::string str)
	{
		result=regexPL.MatchExact(str.c_str());
		return  result.IsMatched();
	}

private:
	static CRegexpT <char> regexRobotPos;
	static CRegexpT <char> regexFileName;
	static CRegexpT <char> regexSpeed; 
	static CRegexpT <char> regexPL; 
	MatchResult result;
};
