/**
*@file
*�ļ����ƣ�CRobotJob.cpp
*
*ժҪ����ҵ�ļ������༭���޸ģ�ɾ����������
*
*@author fly1992@163.com
*
**/
#include "CRobotJob.h"
CDirectory* CJobInterface::pDirOperator=new CDirectory;
///���û�������ҵָ���ļ�·��
const std::string CRobotJob::JOBPATH="\\NandFlash\\RobotJob\\";
///���û�������ҵ�����ļ�·��
const std::string CRobotJobData::JOBDATAPATH="\\NandFlash\\RobotJobData\\";
///���û�������ҵ�����ļ�·��
const std::string CRobotJBR::JBRPATH="\\NandFlash\\RobotJbr\\";
///���û�����Ҫ���͵���ҵ��Ϣ�ļ�·��
const std::string CRobotJBR::RESULTPATH="\\NandFlash\\RobotResult\\";
/**
*@brief ����ָ���ļ�����
*�������ƣ�setJobName
*�������ܣ�����ָ���ļ�����
*@param CStdString ��ҵ���ַ���
**/
void CRobotJob::setJobName(CStdString stdStr)
{
	string str=Tchar2String(stdStr);
	jobPath=FILEPATH+str+".txt";
	jobVector.clear();
	jobVector.push_back("NOP");
	jobVector.push_back("END");
	jobSave();
}
/**
*@brief ���������ļ�����
*�������ƣ�setJobName
*�������ܣ����������ļ�����
*@param CStdString ��ҵ���ַ���
**/
void CRobotJobData::setJobName(CStdString stdStr)
{
	string str=Tchar2String(stdStr);
	jobPath=FILEPATH+str+".txt";
	jobVector.clear();
}
/**
*@brief ����JBR�ļ�����
*�������ƣ�setJobName
*�������ܣ�����JBR�ļ�����
*@param CStdString ��ҵ���ַ���
**/
void CRobotJBR::setJobName(CStdString stdStr)
{
	string str=Tchar2String(stdStr);
	jobPath=FILEPATH+str+".txt";///<�����������ڷ���ָ��
	strData=CRobotJobData::JOBDATAPATH+str+".txt";
	strCommand=CRobotJob::JOBPATH+str+".txt";
	strJBR=JBRPATH+str+".JBR";
	jobName=str;
	jobVector.clear();
}
/**
*@brief ɾ��JBR�ļ�
*�������ƣ�deleteJBRFile
*�������ܣ�ɾ��JBR�ļ�
*@param CStdString ��ҵ���ַ���
**/
void CRobotJBR::deleteJBRFile(string str)
{
	string stringJBR=JBRPATH+str+".JBR";
	CStdString stdStr=StringToTChar(stringJBR);
	pDirOperator->DeleteFileFromDirectory(stdStr.GetData());
}
/**
*@brief ��ȡJBR�ļ���
*�������ƣ�deleteJBRFile
*�������ܣ���ȡJBR�ļ���
*@return CStdString JBR�ļ���
**/
CStdString CJobInterface::getJobName()
{
	return StringToTChar(jobName);
}

///��ȡ��ҵ�ļ�
void CJobInterface::readJob(CStdString stdStr)
{
	string str=Tchar2String(stdStr);
	jobPath=FILEPATH+str+".txt";
	jobVector.clear();
	string strLine;
	std::ifstream ifile(jobPath.c_str());
	while (getline(ifile,strLine))
	{
		jobVector.push_back(strLine);
	}
	ifile.close();
	jobSave();
}
///������ҵ�ļ�
void CJobInterface::jobSave()
{
	std::ofstream file(jobPath.c_str());
	for (int i=0;i<jobVector.size();i++)
	{
		file<<jobVector[i]<<endl;
	}
	file.close();
}
///���뵽��ҵ�ļ���
void CJobInterface::jobInsert(std::string str,int ipos)
{
	if (ipos>=0&&ipos<=jobVector.size())
	{
		jobVector.insert(jobVector.begin()+ipos,str);
	}
	jobSave();
}
///��ָ���ļ���ɾ��
void CRobotJob::jobDelete(int ipos)
{
	if (ipos>0&&ipos<jobVector.size()-1)
	{
		jobVector.erase(jobVector.begin()+ipos);
	}
	jobSave();
}
///�������ļ���ɾ��
void CRobotJobData::jobDelete(int ipos)
{
	jobVector.erase(jobVector.begin()+ipos);
	jobSave();
}
///ɾ���ļ�
void CJobInterface::jobFileDelete(CStdString stdStr) 
{
	stdStr=StringToTChar(FILEPATH)+stdStr+CStdString(_T(".txt"));///<�ɸĳ�const
	pDirOperator->DeleteFileFromDirectory(stdStr.GetData());
}
///��ȡ�ļ����µ������ļ�����
std::vector<TSTRING>& CJobInterface::getJobFileNameVector()
{
	jobNameVector.clear();
	pDirOperator->FindFileFromDirectory(TEXT("NandFlash\\RobotJob"),TEXT("*.txt"),jobNameVector);
	for (int i=0;i<jobNameVector.size();i++)
	{
		int len=jobNameVector[i].length()-FILEPATH.length()-std::string(".txt").length();
		jobNameVector[i]=jobNameVector[i].substr(FILEPATH.length(),len);
	}
	return jobNameVector;
}
///�ϳ�JBR�ļ���������JBR�ļ�
void CRobotJBR::generateFiles()
{
	char* p=const_cast<char *>(strData.c_str());
	pReadFiles->generateFiles(const_cast<char *>(strData.c_str()),const_cast<char *>(strCommand.c_str()),const_cast<char *>(strJBR.c_str()));
	parserJob(strJBR);
}
///����JBR�ļ�
void CRobotJBR::parserJob(string strJbr)
{
	pReadFiles->parserJob(const_cast<char *>(strJbr.c_str()));
	pReadFiles->outResultToFile(const_cast<char *>(jobPath.c_str()));
	//readJob(StringToTChar(jobPath));
}

CJobDisplay::CJobDisplay(CListUIEx* plistui):
					pListUI(plistui),pRobotJob(new CRobotJob),ipc(0),///<ָ�������빹�죬����ָ��Ĭ�Ϲ���
					pRobotJobData(new CRobotJobData),pRobotJBR(new CRobotJBR)
{

}
///ָ����ʾ���б���
void CJobDisplay::jobDisplay()
{
	pListUI->RemoveAll();
	for (int i=0;i<pRobotJob->jobVector.size();i++)
	{
		CStdString strNumber;
		CDialogBuilder builder;
		CStdString strInstr=StringToTChar(pRobotJob->jobVector[i]);
		CListContainerElementUI* pListItem = (CListContainerElementUI*)(builder.Create(_T("ListItem.xml"),(UINT)0));
		if( pListItem != NULL ) 
		{
			pListUI->InsertItem(i,30,pListItem);
			static_cast<CLabelUI*>(pListItem->FindSubControl(_T("Instruction")))->SetText(strInstr);
			strNumber.Format(_T("%d"), i);
			static_cast<CLabelUI*>(pListItem->FindSubControl(_T("Number")))->SetText(strNumber);
		}
	}
}
///���ݵ�ǰPCλ����ʾPCָ���ͷ
void CJobDisplay::pcDisplay()
{
	int listCount=pListUI->GetCount()-1;//��ֹ���
	if (ipc>listCount)
	{
		ipc=0;
	}
	CListContainerElementUI* temp1=static_cast<CListContainerElementUI*>(pListUI->GetItemAt(ipc));
	CListContainerElementUI* temp2=NULL;
	if (ipc==0)
	{
		temp2=static_cast<CListContainerElementUI*>(pListUI->GetItemAt(listCount));
		temp2->SetBkImage(_T(""));
	}
	else
		temp2=static_cast<CListContainerElementUI*>(pListUI->GetItemAt(ipc-1));

	if((temp1 != NULL) && (temp2!= NULL)) 
	{
		temp1->SetBkImage(_T("RobotArrowNew.png"));
		temp2->SetBkImage(_T(""));
	}
}
///����PCָ��
void CJobDisplay::pcDown()
{
	if (ipc>0&&ipc<pListUI->GetCount())
	{
		--ipc;
	}
}
///����PCָ��
void CJobDisplay::pcUp()
{
	if (ipc>=0&&ipc<pListUI->GetCount())
	{
		++ipc;
	}
}
///��ȡPCָ��
int CJobDisplay::getPc()
{
	return ipc;
}
///PCָ������
void CJobDisplay::setPcZero()
{
	ipc=0;
}






