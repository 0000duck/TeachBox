#pragma once

#include <list>
#include "program.h"
#include "JobShowView.h"



class JOBManager
	{
	public:
		JOBManager(void);
		~JOBManager(void);

		void initialize( JobShowView*  jobshow);

		bool openJobfile(char*);
		void newJOB(std::string jobname_ ,int toolnum_ );
		void storeJOB();

        ProgramJOB* getProgramJob();

		void deleteCMDcurrent();

		void insertCMD(Command*);



	private:

        JobShowView *  jobshowview;
		ProgramJOB* jobprogram;

//will do
// 		
// 		void modifyJOB();
// 		void deleteJOB();
// 		void renameJOB();

	};
