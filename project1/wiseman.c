#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

	char buffer[50];
	sprintf(buffer, "0-59/%s * * * * fortune | espeak\n", argv[1]);
	char name[20] = "fileXXXXXX";
	int fd = mkstemp(name);
	FILE *file = fdopen(fd, "w");
	fputs(buffer, file);
	fclose(file);
	char *arr[3] = {"crontab", name, NULL};

	pid_t pid = fork();

	if (pid == 0) {
		execvp("crontab", arr);
	}
	else {
		wait(0);
	}
	remove(name);
	return 0;
}
