/**
*@file
*�ļ����ƣ�CRobotJob.h
*
*ժҪ����ҵ�ļ������༭���޸ģ�ɾ����������
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
///��ҵ������ָ࣬��Ĳ��롢ɾ�����޸ġ����桢setPC��
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
	std::string jobPath;///<�ļ�·��
	const std::string FILEPATH;///<�ļ���·��
	static CDirectory* pDirOperator;
};
///�̳���ҵ������ָ࣬��Ĳ��롢ɾ�����޸ġ������
class CRobotJob:public CJobInterface
{
public:
	CRobotJob():CJobInterface(JOBPATH){};
	void setJobName(CStdString stdStr);
	void jobDelete(int ipos);
	const static std::string JOBPATH;///<�ļ���·��
};
///�̳���ҵ������࣬���ݵĲ��롢ɾ�����޸ġ������
class CRobotJobData:public CJobInterface
{
public:
	CRobotJobData():CJobInterface(JOBDATAPATH){};
	void setJobName(CStdString stdStr);
	void jobDelete(int ipos);
	const static std::string JOBDATAPATH;///<�ļ���·��
};


///�̳���ҵ������࣬��������ҵ�������ļ��Ĳ��롢ɾ�����޸ġ������
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
	const static std::string JBRPATH;///<�ļ���·��
	const static std::string RESULTPATH;

	ReadFiles *pReadFiles;

	string strData;///<����·��
	string strCommand;///<����·��
	string strJBR;///<������·��
};
///��ҵ��ʾ��Ӧ�����ϵ���ҵָ���ࡢ��ҵ�������JBR��
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