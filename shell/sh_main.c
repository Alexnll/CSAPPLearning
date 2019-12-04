#include "sh_main.h"

int main(int argc, char ** argv){

	char cmdline[MAXLINE]; // for storing the input command line

	while(1){
		/* read */
		printf("> ");
		Fgets(cmdline, MAXARGS, stdin);
		if(feof(stdin)) exit(0);
		
		/* evaluate the command line */
		eval(cmdline);	
	}
}
