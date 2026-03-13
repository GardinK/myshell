#include <stdio.h> 
#include <string.h> 

int main() {
	char buffer [1024];
	char *args[64];
	char *token;
	int i = 0;
	
	while (1) {
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

	}
	return 0;
}
