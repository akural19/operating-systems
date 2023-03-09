# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <string.h>
# include <signal.h>

# define BUFFER_SIZE 50
# define READ_END 0
# define WRITE_END 1

int main() {
	char writeMessage[BUFFER_SIZE];
	char readMessage[BUFFER_SIZE];
	pid_t pid;
	int fd1[2];
	int fd2[2];
	int fd3[2];
	int fd4[2];
	pid_t firstChild;
	pid_t pids[2];

	if (pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1 || pipe(fd4) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	
	pid = getpid();

	for (int ii = 0; ii < 2; ii++) {
		if (ii == 1 && pid == 0) {
			firstChild = getpid();
		}
		if (pid > 0) {
			if (ii == 1) {
				firstChild = pid;
			}
			sleep(5);
			pid = fork();
			pids[ii] = pid;
		}
	}
	if (pid > 0) {  
		close(fd1[READ_END]);
		close(fd2[READ_END]);
		close(fd3[WRITE_END]);
		close(fd4[WRITE_END]);
		
		scanf("%s", writeMessage);
		write(fd1[WRITE_END], writeMessage, strlen(writeMessage) + 1);
		write(fd2[WRITE_END], writeMessage, strlen(writeMessage) + 1);

		char newReadMessage[BUFFER_SIZE];
		read(fd3[READ_END], readMessage, BUFFER_SIZE);
		read(fd4[READ_END], newReadMessage, BUFFER_SIZE);

		float floatValue = atof(newReadMessage);	
		float result = atoi(readMessage) + floatValue;

		printf("Final Result: %.3f\n", result);

		close(fd1[WRITE_END]);
		close(fd2[WRITE_END]);
		close(fd3[READ_END]);
		close(fd4[READ_END]);

		for (int ii = 0; ii < 2; ii++) {
			sleep(5);
			kill(pids[ii], SIGKILL);
		}
	}
	else if (pid == 0) { ;
		if (getpid() == firstChild) {
			close(fd1[WRITE_END]);
			close(fd3[READ_END]);

			read(fd1[READ_END], readMessage, BUFFER_SIZE);			
			int num = atoi(readMessage) * getpid();

			printf("First Child: Input %s, Output %d * %s\n", readMessage, getpid(), readMessage);
			sprintf(writeMessage, "%d", num);
			write(fd3[WRITE_END], writeMessage, strlen(writeMessage) + 1);
 			
			close(fd1[READ_END]);
			close(fd3[WRITE_END]);
		}
		else {
			close(fd2[WRITE_END]);
			close(fd4[READ_END]);
                                                                        
			read(fd2[READ_END], readMessage, BUFFER_SIZE);			
			float num = (float) getpid() / (float) atoi(readMessage);
                                                                        
			printf("Second Child: Input %s, Output %d / %s\n", readMessage, getpid(), readMessage);
			sprintf(writeMessage, "%f", num );
			write(fd4[WRITE_END], writeMessage, strlen(writeMessage) + 1);

			close(fd2[READ_END]);
			close(fd4[WRITE_END]);
		}
	}
	return 0;
}
