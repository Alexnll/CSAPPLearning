#include "sh_main.h"

/* eval - Evaluate a command line */
void eval(char * cmdline){
	
	char * argv[MAXARGS]; // pointer array, for store the argument list
	char buf[MAXARGS]; // Hold modified command line
	int bg; // shoud the job run in bg or fg
	pid_t pid;
	
	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL) return; // Ignore empty lines

	if (!builtin_command(argv)){
		if (pid = Fork() == 0){ // Child runs user job
			if (execve(argv[0], argv, environ) < 0){
				printf("%s: Command not found.\n", argv[0]);
				exit(0);
			}
		}

		// {arent waits for foreground job to  terminate
		if (!bg){

			int status;
			if (waitpid(pid, &status, 0) < 0)
				unix_error("waitfg: waitpid error");
		}
		else
			printf("%d %s", pid, cmdline);
	}
	return;
}

/* if first arg is a builtin command, run it and return true */
/* for this program, the only builtin command is "exit" */
int builtin_command(char ** argv){

	if (!strcmp(argv[0], "quit"))
		exit(0);  
	if (!strcmp(argv[0], "&"))
		return 1;

	return 0; // not a builtin command
}

/* parseline - Parse the command line and bild the argv array */
int parseline(char * buf, char ** argv){
	
	char * delim; // points to first space delimiter
	int argc; // number of args
	int bg; // bg job?

	buf[strlen(buf)-1] = ' ';
	while (*buf && (*buf == ' '))
		buf++;

	// build the argv list
	argc = 0;
	while ((delim = strchr(buf, ' '))) {
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		// ignore spaces
		while(*buf && (*buf == ' '))
			buf++;
	}
	argv[argc] = NULL;

	// ignore blank line
	if (argc == 0)
		return 1;

	// should the job run in the bg?
	if ((bg = (*argv[argc-1] == '&')) == 0)
		argv[--argc] = NULL;

	return bg;
}
