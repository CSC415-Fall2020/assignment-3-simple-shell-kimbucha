/**************************************************************
* Class:  CSC-415-02 FALL 2020
* Name:kim nguyen
* Student ID:920766012
* GitHub UserID:kimbucha
* Project: Assignment 3 – Simple Shell
*
* File: nguyen_kim_HW3_main.c
*
* Description:
*
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_COUNT 512


// NOTES--------------------------------------------------------------------------------------------------------------------
// parse input string, store into collection of substrings (store pointers to substrings in arrayy) -> to pass into execvp
//	included NULL ptr in array after the last substrings so arr would hold n+1 elements bc NULL
// if usr enter empty line, report error and fetch new line of input
// if user enter exit cmd, shell terminates

// then fork for 2 processes: parent/child
// parent waits for child to DIE
// child uses exec to kermit suicide

// if parents PID = 100 & childs PID = 101
// then childs PPID = parents PID = 100




int main(){

	char usr_input[BUFFER_COUNT];
	char *cmd[69];
	char *tok;
	char *envPath ="/bin/";
	char path[69];

	while(1){							// get into loop
		printf("prompt$: ");					// display required prompt

		if(fgets(usr_input, BUFFER_COUNT, stdin)){
                	if( strncmp(usr_input, "exit", 4) == 0)		// if error when usr input, ADIOS
                        	break;

	                size_t length = strlen(usr_input);

	                if( usr_input[length - 1] == '\n')		//replace last element w/ NULL TERMINATE
        	                usr_input[length - 1] = '\0';

      	          	int i = 0;

                	tok = strtok(usr_input, " ");			//tokenize

                	while( tok!= NULL){
                        	cmd[i] = tok;
                        	i++;
                        	tok = strtok(NULL, " ");
                	}
                	cmd[i] = NULL;
        	}
        	else exit(0);

		pid_t pid;
      		int status;

        	if (fork() == 0) {					// CHILD
                	printf("Child process, PID: %d", getpid());

			strcpy(path, envPath);
			strcat(path, cmd[0]);

			if (execvp(path, cmd) < 0) {			// CHILD EXECS AND DIES
    	       			perror("exec");
        	        	exit(2);
                	}
      		}
	        else {
			pid = wait(&status);				// parent waits for child to die
        	        if( WIFEXITED(status))
				printf("Child %d, exited with %d\n", pid, WEXITSTATUS(status));
 	       }
	}
	return 0;
}
