#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> 

#include "ReadFiles.h"

using namespace std;


ReadFiles::ReadFiles(void)
{

}
ReadFiles::~ReadFiles()
{

}
void ReadFiles::outResultToFile(char* outFile)
{

	ofstream writeFiles;
	writeFiles.open(outFile,ios::trunc);

	CommandSegment* cmdSegment = resultOfJob->cmdseg;
	CommandSegment::iterator cmdBegin = cmdSegment->begin();
	
	int sizeOfcmd = cmdSegment->size();

	for (int numcmd_ = 0;cmdBegin != cmdSegment->end();cmdBegin++ , numcmd_++)
	{	
		if ((numcmd_ > 0)  && (numcmd_ < sizeOfcmd-1))
		{
			writeFiles<<(*cmdBegin)->showinfo(numcmd_)<<endl;
		}	
	}

	writeFiles.close();
}




void ReadFiles::parserJob(char* jobName)
{
	resultOfJob = openAndparser(jobName);

}

int ReadFiles::CountLines(char *filename)
{
	ifstream ReadFile;
	int n=0;
	char line[512];
	string temp;
	ReadFile.open(filename,ios::in);//ios::in ��ʾ��ֻ���ķ�ʽ��ȡ�ļ�
	if(ReadFile.fail())//�ļ���ʧ��:����0
	{
		return 0;
	}
	else//�ļ�����
	{
		while(getline(ReadFile,temp))
		{
			n++;
		}
		return n;
	}
	ReadFile.close();
}



void ReadFiles::generateFiles(char* dataFile,char* commandFile,char* jobFile)
{

	ofstream readAndWrite;

	char buffer[256];
	fstream out;

	
	int lineNumberOfData;
	lineNumberOfData = CountLines(dataFile);

	out.open(dataFile,ios::in);
	readAndWrite.open(jobFile);//����������jobFile��

	readAndWrite<<"/DIR\n"<<"/JOB\n"<<"//NAME ";
	readAndWrite<<jobFile<<endl;
	readAndWrite<<"//POS\n"<<"///NPOS "<<lineNumberOfData<<",0,0,0,0,0\n"; 
	readAndWrite<<"///TOOL "<<0<<"\n";// "0" needs to be changed.
	readAndWrite<<"///POSTYPE PULSE\n";
	readAndWrite<<"///PULSE\n";

	while(!out.eof())
	{
		out.getline(buffer,256,'\n');//getline(char *,int,char) ��ʾ�����ַ��ﵽ256�����������оͽ���
		readAndWrite<<buffer<<endl;
	}
	out.close();

	SYSTEMTIME st;
	GetLocalTime( &st ); 

	fstream command;

	command.open(commandFile,ios::in);

	readAndWrite<<"//INST\n";
	readAndWrite<<"///DATE "<<st.wYear<<'/'<<st.wMonth<<'/'<<st.wDay<<'/'<<st.wHour<<'/'<< st.wMinute<<"\n";
	readAndWrite<<"///COMM By XX\n";
	readAndWrite<<"///ATTR SC,RW\n";
	readAndWrite<<"///GROUP1 RB1\n";

	while(!command.eof())
	{
		command.getline(buffer,256,'\n');
		readAndWrite<<buffer<<endl;
	}
	command.close();
}



