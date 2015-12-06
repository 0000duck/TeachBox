/**
*@file
*文件名称：CRobotJob.h
*
*摘要：作业文件处理，编辑，修改，删除，解析等
*
*@author fly1992@163.com
*
**/
#pragma once
#include <vector>
#include <fstream>
#include "GlobalVar.h"
#include "Directory.h"
#include "ReadFiles.h"
///作业处理基类，指令的插入、删除、修改、保存、setPC等
class CJobInterface
{
public:
	CJobInterface(string strPath):FILEPATH(strPath){};
	virtual void setJobName(CStdString stdStr)=0;
	void readJob(CStdString stdStr);
	void jobInsert(std::string str,int ipos);
	virtual void jobDelete(int ipos)=0;
	void jobSave();
	void jobFileDelete(CStdString stdStr);
	std::vector<TSTRING>& getJobFileNameVector();
	std::vector<TSTRING> jobNameVector;
	std::vector<std::string> jobVector;
	CStdString getJobName();
protected:
	std::string jobName;
	std::string jobPath;///<文件路径
	const std::string FILEPATH;///<文件夹路径
	static CDirectory* pDirOperator;
};
///继承作业处理基类，指令的插入、删除、修改、保存等
class CRobotJob:public CJobInterface
{
public:
	CRobotJob():CJobInterface(JOBPATH){};
	void setJobName(CStdString stdStr);
	void jobDelete(int ipos);
	const static std::string JOBPATH;///<文件夹路径
};
///继承作业处理基类，数据的插入、删除、修改、保存等
class CRobotJobData:public CJobInterface
{
public:
	CRobotJobData():CJobInterface(JOBDATAPATH){};
	void setJobName(CStdString stdStr);
	void jobDelete(int ipos);
	const static std::string JOBDATAPATH;///<文件夹路径
};


///继承作业处理基类，机器人作业解析后文件的插入、删除、修改、保存等
class CRobotJBR:public CJobInterface
{
public:
	CRobotJBR():CJobInterface(RESULTPATH),pReadFiles(new ReadFiles){};
	void setJobName(CStdString stdStr);
	void jobDelete(int ipos){};
	void generateFiles();
	void parserJob(string str);
	void deleteJBRFile(string str);
private:
	const static std::string JBRPATH;///<文件夹路径
	const static std::string RESULTPATH;

	ReadFiles *pReadFiles;

	string strData;///<数据路径
	string strCommand;///<命令路径
	string strJBR;///<输出结果路径
};
///作业显示，应用以上的作业指令类、作业数据类和JBR类
class CJobDisplay
{
public:
	CJobDisplay(CListUIEx* plistui);
	void jobDisplay();
	void pcDisplay();
	int getPc();
	void pcDown();
	void pcUp();
	void setPcZero();
	CJobInterface* pRobotJob;
	CJobInterface* pRobotJobData;
	CRobotJBR* pRobotJBR;
private:
	CListUIEx* pListUI;
	int ipc;
};