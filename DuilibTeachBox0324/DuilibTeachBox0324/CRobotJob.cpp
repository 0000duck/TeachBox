/**
*@file
*文件名称：CRobotJob.cpp
*
*摘要：作业文件处理，编辑，修改，删除，解析等
*
*@author fly1992@163.com
*
**/
#include "CRobotJob.h"
CDirectory* CJobInterface::pDirOperator=new CDirectory;
///设置机器人作业指令文件路径
const std::string CRobotJob::JOBPATH="\\NandFlash\\RobotJob\\";
///设置机器人作业数据文件路径
const std::string CRobotJobData::JOBDATAPATH="\\NandFlash\\RobotJobData\\";
///设置机器人作业解析文件路径
const std::string CRobotJBR::JBRPATH="\\NandFlash\\RobotJbr\\";
///设置机器人要发送的作业信息文件路径
const std::string CRobotJBR::RESULTPATH="\\NandFlash\\RobotResult\\";
/**
*@brief 设置指令文件名字
*函数名称：setJobName
*函数功能：设置指令文件名字
*@param CStdString 作业名字符串
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
*@brief 设置数据文件名字
*函数名称：setJobName
*函数功能：设置数据文件名字
*@param CStdString 作业名字符串
**/
void CRobotJobData::setJobName(CStdString stdStr)
{
	string str=Tchar2String(stdStr);
	jobPath=FILEPATH+str+".txt";
	jobVector.clear();
}
/**
*@brief 设置JBR文件名字
*函数名称：setJobName
*函数功能：设置JBR文件名字
*@param CStdString 作业名字符串
**/
void CRobotJBR::setJobName(CStdString stdStr)
{
	string str=Tchar2String(stdStr);
	jobPath=FILEPATH+str+".txt";///<输出结果，用于发送指令
	strData=CRobotJobData::JOBDATAPATH+str+".txt";
	strCommand=CRobotJob::JOBPATH+str+".txt";
	strJBR=JBRPATH+str+".JBR";
	jobName=str;
	jobVector.clear();
}
/**
*@brief 删除JBR文件
*函数名称：deleteJBRFile
*函数功能：删除JBR文件
*@param CStdString 作业名字符串
**/
void CRobotJBR::deleteJBRFile(string str)
{
	string stringJBR=JBRPATH+str+".JBR";
	CStdString stdStr=StringToTChar(stringJBR);
	pDirOperator->DeleteFileFromDirectory(stdStr.GetData());
}
/**
*@brief 获取JBR文件名
*函数名称：deleteJBRFile
*函数功能：获取JBR文件名
*@return CStdString JBR文件名
**/
CStdString CJobInterface::getJobName()
{
	return StringToTChar(jobName);
}

///读取作业文件
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
///保存作业文件
void CJobInterface::jobSave()
{
	std::ofstream file(jobPath.c_str());
	for (int i=0;i<jobVector.size();i++)
	{
		file<<jobVector[i]<<endl;
	}
	file.close();
}
///插入到作业文件中
void CJobInterface::jobInsert(std::string str,int ipos)
{
	if (ipos>=0&&ipos<=jobVector.size())
	{
		jobVector.insert(jobVector.begin()+ipos,str);
	}
	jobSave();
}
///从指令文件中删除
void CRobotJob::jobDelete(int ipos)
{
	if (ipos>0&&ipos<jobVector.size()-1)
	{
		jobVector.erase(jobVector.begin()+ipos);
	}
	jobSave();
}
///从数据文件中删除
void CRobotJobData::jobDelete(int ipos)
{
	jobVector.erase(jobVector.begin()+ipos);
	jobSave();
}
///删除文件
void CJobInterface::jobFileDelete(CStdString stdStr) 
{
	stdStr=StringToTChar(FILEPATH)+stdStr+CStdString(_T(".txt"));///<可改成const
	pDirOperator->DeleteFileFromDirectory(stdStr.GetData());
}
///获取文件夹下的所有文件名称
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
///合成JBR文件，并解析JBR文件
void CRobotJBR::generateFiles()
{
	char* p=const_cast<char *>(strData.c_str());
	pReadFiles->generateFiles(const_cast<char *>(strData.c_str()),const_cast<char *>(strCommand.c_str()),const_cast<char *>(strJBR.c_str()));
	parserJob(strJBR);
}
///解析JBR文件
void CRobotJBR::parserJob(string strJbr)
{
	pReadFiles->parserJob(const_cast<char *>(strJbr.c_str()));
	pReadFiles->outResultToFile(const_cast<char *>(jobPath.c_str()));
	//readJob(StringToTChar(jobPath));
}

CJobDisplay::CJobDisplay(CListUIEx* plistui):
					pListUI(plistui),pRobotJob(new CRobotJob),ipc(0),///<指针对象必须构造，不能指望默认构造
					pRobotJobData(new CRobotJobData),pRobotJBR(new CRobotJBR)
{

}
///指令显示到列表中
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
///根据当前PC位置显示PC指针箭头
void CJobDisplay::pcDisplay()
{
	int listCount=pListUI->GetCount()-1;//防止溢出
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
///上移PC指针
void CJobDisplay::pcDown()
{
	if (ipc>0&&ipc<pListUI->GetCount())
	{
		--ipc;
	}
}
///下移PC指针
void CJobDisplay::pcUp()
{
	if (ipc>=0&&ipc<pListUI->GetCount())
	{
		++ipc;
	}
}
///获取PC指针
int CJobDisplay::getPc()
{
	return ipc;
}
///PC指针置零
void CJobDisplay::setPcZero()
{
	ipc=0;
}






