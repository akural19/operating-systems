# include <sys/types.h>
# include <time.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>

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
	pid = fork();
		
	if (pid == 0) {
		while (true) {
			buffer = returnTime();
			printf("Process %d printing: %s\n",getpid(),buffer);
			sleep(1);
		}
	}
	if (pid > 0) {
		sleep(5);
		kill(pid, SIGKILL);
		printf("Child %d killed!\n", pid);
	}
	return 0;
}
