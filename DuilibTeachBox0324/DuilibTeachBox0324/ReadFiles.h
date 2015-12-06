#ifndef READFILES_H
#define READFILES_H

#include "Program.h"


using namespace std;

class ReadFiles
{
public:
	ReadFiles(void);
	~ReadFiles();

	//从dataFile文件和command文件生成jobFile文件
	void generateFiles(char* dataFile,char* commandFile,char* jobFile);

	//编译名为Job文件
	void parserJob(char* Job);

	//将编译结果输出名为outFile的文件，格式为：命令号  6个关节角  速度值
	void outResultToFile(char* outFile);


	

private:

	ProgramJOB *resultOfJob;//编译Job文件的结果

	int CountLines(char *filename);//计算一个文件的行数
};




#endif
