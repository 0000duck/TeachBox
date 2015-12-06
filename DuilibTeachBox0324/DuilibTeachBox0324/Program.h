#ifndef PROGRAM_H
#define PROGRAM_H

#include<iostream>
#include<vector>
#include<list>
#include <string>
#include<map>
#include<sstream>



#ifdef INFORMDLL
#define INFORMDLL  __declspec(dllimport)
#else
#define INFORMDLL  __declspec(dllexport)
#endif


using namespace std;


class /*INFORMDLL*/ DataItem;
class /*INFORMDLL*/  Command;
class ProgramJOB;
// template class __declspec(dllexport) std::list<DataItem*>;  
// template class __declspec(dllexport) std::list<Command*>;  
//extern  ProgramJOB* open_parser(char* afile);

INFORMDLL ProgramJOB* openAndparser(char* afile);

typedef  std::list<DataItem*> DataSegment;
typedef  std::list<Command*> CommandSegment;
typedef  std::map<int,DataItem*> PointsinINT;

/************************************************************************/
/* 整个程序由数据段和指令段组成    */
/*加上一些注释信息
/************************************************************************/
class INFORMDLL ProgramJOB
	{
	public :
		ProgramJOB();
		~ProgramJOB();

		void initialize(char*  ,int  );

		DataSegment* dataseg;
		CommandSegment* cmdseg;

		char* jobname ;
		int num_cpoint , num_ppoint ;
		int toolnum ;
		int group1,group2 ;

		void jobGenerate(std::string filepath);
	};

class INFORMDLL DataItem
	{
	public:
		DataItem();
		~DataItem();

		int number;
		int size; 
		double data[7];

		enum TYPE {PULSE,ROBOT};
		TYPE datatype;

		std::string toCode(int);
	};



class  INFORMDLL  AddtionItem
	{
	public: 
		AddtionItem();
		~AddtionItem();
		enum ADDITEMTYPE {V,VJ,PL,ACC,DEC};

		ADDITEMTYPE tagtype;
		double valuetag;

		virtual std::string showinfo_add();
	};

class INFORMDLL Command
	{
	public :

		Command();
		 ~Command();

		enum INSTYPE {NOP,END,MOVJ,MOVL,MOVC,IMOV,MOVS};
		INSTYPE instype;

		DataItem* point;//位置值

		AddtionItem* additems[5];
		//virtual void executedo()=0;
		virtual std::string showinfo(int i);

		virtual std::string showinfo();

		std::string toCode(int);
	};

// class INFORMDLL CtlCommand : public Command
// 	{
// 	public :
// 		CtlCommand();
// 		virtual ~CtlCommand(); 
// 
// 		virtual void executedo()=0;
// 	};
// 
// class INFORMDLL NOPCommand : public CtlCommand
// 	{
// 	public: 
// 		    NOPCommand();
// 			virtual ~NOPCommand();
// 
// 			virtual void executedo();
// 	};
// 
// class INFORMDLL ENDCommand : public CtlCommand
// 	{
// 	public: 
// 		ENDCommand();
// 		virtual ~ENDCommand();
// 
// 		virtual void executedo();
// 	};
// 
// 
// class INFORMDLL MOVECommand : public Command
// 	{
// 	public :
// 		MOVECommand();
// 		virtual ~MOVECommand();
// 
// 		virtual void executedo();
// 	};
// 
// class INFORMDLL MOVJCommand : public MOVECommand
// 	{
// 	public :
// 		MOVJCommand();
// 		virtual ~MOVJCommand();      
// 
//         virtual void executedo();
// 	};
// 
// class INFORMDLL MOVCCommand : public MOVECommand
// 	{
// 	public :
// 		MOVCCommand();
// 		virtual ~MOVCCommand();      
// 
// 		virtual void executedo();
// 	};
// 
// class INFORMDLL MOVLCommand : public MOVECommand
// 	{
// 	public :
// 		MOVLCommand();
// 		virtual ~MOVLCommand();     
// 
// 		virtual void executedo();
// 	};
// 






#endif