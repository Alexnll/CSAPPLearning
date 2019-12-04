#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAXLINE 8192
#define MAXARGS 128

extern char ** environ; // unifinish

void eval(char * cmdline);
int parseline(char * buf, char ** argv);
int builtin_command(char ** argv);
void unix_error(char * msg);
pid_t Fork(void);
char * Fgets(char *ptr, int n, FILE * stream); // unifinish
