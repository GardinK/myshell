#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <sys/wait.h>

int main() {
	char buffer [1024];
	char *args[64];
	char *token;
	int i;
	
	while (1) {
		
		i = 0;
		printf("myshell> ");
		fgets(buffer, 1024, stdin);

		buffer[strcspn(buffer, "\n")] = '\0'; 
		
		if (strcmp(buffer, "exit") == 0 ) {
			break;
		}
		token = strtok(buffer, " ");
		while (token != NULL) {
			args[i++] = token;
			token = strtok(NULL, " ");
		}
			
		args[i] = NULL;

		if (strcmp(args[0], "cd") == 0) {
			char *path;
			if (args[1] == NULL)
				path = getenv("HOME");
			else
				path = args[1];
			
			if (chdir(path) == -1) {
				perror(args[1]);
			}	
		} else {

			pid_t pid = fork();

			if (pid == 0) {
				execvp(args[0], args);
				perror(args[0]);
				exit(1);
			} else {
				int status;
				waitpid(pid, &status, 0);
			}	
		}
	}

	return 0;

}
