# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int main(int argc, char *argv[]) {

	pid_t pid = getpid();
	int numChild = 1;

	const char *executable = argv[1];
	const int totChild = atoi(argv[2]);
	const char *message = argv[3];
	
	if (totChild < 2) {
		exit(EXIT_FAILURE);
	}
	
	printf("Parent: Playing Chinese whisper with %d processes.\n", totChild);
	for (int ii = 0; ii < totChild; ii++) {
		if (pid > 0) {
			pid = fork();
			if (pid > 0) {
				wait(NULL);
				numChild++;
			}
		}
	}
	

	if (pid == 0) {
		char buffer1[25];
		char buffer2[25];

		sprintf(buffer1, "%d", numChild);
		sprintf(buffer2, "%d", totChild);
		char *arr[] = {executable, message, buffer1, buffer2, NULL};
		execve(executable, arr, 0);
	}
	else {
		printf("Parent terminating...\n");
	}
	return 0;
}
