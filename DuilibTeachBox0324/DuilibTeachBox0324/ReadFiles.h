#ifndef READFILES_H
#define READFILES_H

#include "Program.h"


using namespace std;

class ReadFiles
{
public:
	ReadFiles(void);
	~ReadFiles();

	//��dataFile�ļ���command�ļ�����jobFile�ļ�
	void generateFiles(char* dataFile,char* commandFile,char* jobFile);

	//������ΪJob�ļ�
	void parserJob(char* Job);

	//�������������ΪoutFile���ļ�����ʽΪ�������  6���ؽڽ�  �ٶ�ֵ
	void outResultToFile(char* outFile);


	

private:

	ProgramJOB *resultOfJob;//����Job�ļ��Ľ��

	int CountLines(char *filename);//����һ���ļ�������
};




#endif
