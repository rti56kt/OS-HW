#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE 80

int main(void)
{
	char *arg[MAX_LINE/2+1]; /*command line arguments*/
	int should_run = 1; /*flag to determine when to exit program*/
	pid_t pid;

	while(should_run){
		printf("osh>");
		fflush(stdout);

		char inputBuffer[MAX_LINE] = {'\0'};
		int head = 0, tail = 0, arg_cnt = 0;

		read(STDIN_FILENO, inputBuffer, MAX_LINE);
		
		int in_buf_len = strlen(inputBuffer);
		inputBuffer[in_buf_len-1] = '\0';
		
		if(!strcmp(inputBuffer, "exit")){
			should_run = 0;
			break;
		}
		arg[0] = strtok(inputBuffer, " ");
		while(arg[arg_cnt] != NULL){
			arg_cnt++;
			arg[arg_cnt] = strtok(NULL, " ");
		}
		arg_cnt--;
		if(!strcmp(arg[arg_cnt], "&")){
			arg[arg_cnt] = NULL;
			pid = fork();
			if(pid == 0) execvp(arg[0], arg);
		}else{
			pid = fork();
			if(pid == 0) execvp(arg[0], arg);
			else waitpid(pid, NULL, 0);
		}
		
		/**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will not invoke wait()
		*/
	}

	return 0;
}

