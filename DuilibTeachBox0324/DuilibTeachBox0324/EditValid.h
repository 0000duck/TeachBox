/**
*@file
*文件名称：EditValid.h
*
*摘要：输入信息校验，判断是否合理
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
	///判断机器人位置信息是否合理
	bool isValidRobotPos(std::string str)
	{
		result=regexRobotPos.MatchExact(str.c_str());
		return  result.IsMatched();
	}
	///判断机器人作业文件名信息是否合理
	bool isValidFileName(std::string str)
	{
		result=regexFileName.MatchExact(str.c_str());
		return  result.IsMatched();
	}
	///判断机器人速度信息是否合理
	bool isValidSpeed(std::string str)
	{
		result=regexSpeed.MatchExact(str.c_str());
		return  result.IsMatched();
	}
	///判断机器人PL信息是否合理
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
