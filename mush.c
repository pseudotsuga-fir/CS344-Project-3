#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_PATH_LEN 200

int main(void) {
	while(1) {
		char input_s[2048];
		char *new_argv[128];
		char path[MAX_PATH_LEN];
		getcwd(path, MAX_PATH_LEN);
		printf("~ %s $ ", path);
		fgets(input_s, sizeof input_s, stdin);
		int i = 0;
		if ((new_argv[0] = strtok(input_s, " \t\n\r")) != NULL) {
			do {
				i++;
			} while ((new_argv[i] = strtok(NULL, " \t\n\r")) != NULL);
		}
		else {
			continue;
		}

		if (strcmp(new_argv[0], "cd") == 0) {
			if (chdir(new_argv[1]) < 0) {
				perror("chdir");
			}
		}
		else if (strcmp(new_argv[0], "exit") == 0) {
			exit(0);
		}
		else { 
			pid_t pid = fork();
			if (pid == 0) {	
				execvp(new_argv[0], new_argv);
				perror("exec");
				exit(1);
			}
			wait(NULL);
		}
	}
}
