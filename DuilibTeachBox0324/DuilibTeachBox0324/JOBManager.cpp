#include "JOBManager.h"
#include<cnoid/MessageView>

using namespace std;
using namespace cnoid;
JOBManager::JOBManager(void)
	{
	}

JOBManager::~JOBManager(void)
	{
	}


bool JOBManager::openJobfile( char* filepath)
	{
            jobprogram = openAndparser(filepath); 
			if (jobprogram==0 )
			    return false;
			return true;
	}



void JOBManager::newJOB( std::string jobname_ ,int toolnum_ )
	{
           jobprogram = new ProgramJOB() ;

           char*  soucechar= const_cast<char*>(jobname_.c_str());
            char * temp = new char[20];
			int i = 0;
			while(*soucechar!='\0')
				           {			temp[i] = *soucechar;
                                             ++i;
											 ++soucechar;
	                      }    temp[i]='\0';        

		   jobprogram->initialize(temp,toolnum_);
	 
	}

ProgramJOB* JOBManager::getProgramJob()
	{
               return jobprogram;
	}

void JOBManager::initialize( JobShowView * jobshow )
	{
                     jobshowview = jobshow;
	}

void JOBManager::deleteCMDcurrent()
	{
            jobshowview->deleteJobCMD();
	}

void JOBManager::insertCMD( Command* cmdinsert)
	{
          jobshowview->insertJobCMD(cmdinsert);
	}

void JOBManager::storeJOB()
	{
            if(! jobprogram)  return;



			 string temp = string("..\\share\\job\\")+string(jobprogram->jobname);
		     MessageView::instance()->putln(jobprogram->jobname);

                jobprogram->cmdseg = jobshowview->getCMDlistpoint();
                jobprogram->jobGenerate(temp);
	}
