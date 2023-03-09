# include <sys/types.h>
# include <time.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# define NUM_CHILD 4

char *returnTime() {
	
	struct timeval tv; 
	time_t t;
	struct tm *var;
	char buffer[20];

	gettimeofday(&tv, NULL);
	t = tv.tv_sec;
	
	var = localtime(&t);
	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",var);
	return strdup(buffer);
}

int main() {

	pid_t pid = getpid();
	char *buffer;
	pid_t pids[4];

	for (int ii = 0; ii < NUM_CHILD; ii++) {
		if (pid > 0) {
			pid = fork();
			pids[ii] = pid;
		}
	}
	if (pid == 0) {
		while (true) {
			buffer = returnTime();
			printf("Process %d printing: %s\n",getpid(),buffer);
			sleep(1);
		}
	}
	if (pid > 0) {
		sleep(5);
		for (int ii = 0; ii < NUM_CHILD; ii++) {
			kill(pids[ii], SIGKILL);
			printf("Child %d killed!\n", pids[ii]);
		}
	}
	return 0;
}
