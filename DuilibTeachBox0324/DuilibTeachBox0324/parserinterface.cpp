
include "parserinterface.h"




extern int yyparse();
extern FILE *yyin;

void  open_parser(char* jobfile)
	{
	         /*const char* namejob = jobfile.c_str();*/
	        yyin = fopen(jobfile,"r");
			yyparse();
	}