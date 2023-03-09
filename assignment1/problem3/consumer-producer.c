# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/shm.h>
# include <sys/stat.h>
# include <sys/mman.h>

int writeFunc(char *message, int numChild) {

	int shm_fd;
	const int SIZE = 4096;
	const char *name = "OS";
	
	if (numChild == 1) {
		shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
        	ftruncate(shm_fd,SIZE);
	}
	else {
		shm_fd = shm_open(name, O_RDWR, 0666);
	}
                                                                                  
        void *ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

        if (ptr == MAP_FAILED) {
        	printf("Map failed\n");
        	return -1;
        }

        sprintf(ptr,"%s%c", message, '\0');
        ptr += (strlen(message) + 1);
	printf("Child %d: %s\n", numChild, message);
	return 0;
}

char *readFunc(int numChild, int  totChild) {

	const char* name = "OS";	
	const int SIZE = 4096;

	int shm_fd = shm_open(name, O_RDONLY, 0666);

       	if (shm_fd == -1) {
       		printf("Shared memory failed\n");
       		exit(-1);
       	}
                                                             
        void *ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        
	if (ptr == MAP_FAILED) {
        	printf("Map failed\n");
        	exit(-1);
        }

	return ptr;
}

int main(int argc, char *argv[]) {

	char *message = argv[1];
	const int numChild = atoi(argv[2]);
	const int totChild = atoi(argv[3]);
	int boundary;
	int randNumber1;
	int randNumber2;
	
	struct timeval tv; 
	suseconds_t tv_usec;

	gettimeofday(&tv, NULL);
	tv_usec = tv.tv_usec;

	srand(tv_usec);
	if (numChild == 1) {
		writeFunc(message, numChild);
	}
	else {
		message = readFunc(numChild, totChild);	
		message = strdup(message);
		int boundary = strlen(message);
		
		randNumber1 = rand() % boundary;
		randNumber2 = rand() % boundary;
		
		char *temp = message[randNumber1];
		message[randNumber1] = message[randNumber2];
		message[randNumber2] = temp;
		writeFunc(message, numChild);
		free(message);
		if (numChild == totChild) {
			if (shm_unlink("OS") == -1) {
                        	printf("Error removing %s\n", "OS");
                        	exit(-1);
                        }                                                   
		}
	}
}                                                                     
