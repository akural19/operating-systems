#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

	// redirection(read from a file, write to a file and append to a file) is applicable to uniq command
	// position of the input file and flag arguments can change place without problem

	char *buffer;                                    
        char *prev;                                      	     
        size_t bufSize = 50;                                   
        int flag = 0;                                          
        FILE *file;
	int counter;

        buffer = (char *) malloc(bufSize*sizeof(char));              
        prev = (char *) malloc(bufSize*sizeof(char));          
        
	bool boolean1 = false;
	bool boolean2 = false;

	if (argc >= 2) {
		boolean1 = (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--count") == 0); 	
	}
	if (argc >= 3) {
		boolean2 = (strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "--count") == 0); 
	}
	bool boolean = boolean1 || boolean2;

	if (argc >= 2 && argv[1] != NULL && boolean1 == false) {	
        	file = fopen(argv[1], "r");                   
	}	
	else if (argc >= 3 && argv[2] != NULL && boolean2 == false) {
		file = fopen(argv[2] , "r");
	}
	else {
		file = stdin;
	}
        if (buffer == NULL) {                                        
        	perror("Unable to allocate buffer!");            
              	exit(1);                                      
        }                                                      
        if (file == NULL) {                                    
              	perror("Unable to open the file!");              
              	exit(1);                                      
        }                                                      
        while (1) {                                            
              	char *string = fgets(buffer, bufSize, file);      
              	if (string == NULL) {                           
              		break;
              	}
              	buffer[strcspn(buffer, "\n")] = '\0';
              	if (flag == 0) {                                 
              		strcpy(prev, buffer);                    
                  	counter = 1;
              		flag = 1;                                
              	}                                                
              	else {                                           
              		if (strcmp(buffer, prev) != 0) {
			       if (boolean) {
			       		printf("\t%d %s\n", counter, prev);
			       }
				else {
					 printf("%s\n", prev);
				}
              			strcpy(prev, buffer);            
           			counter = 1;
              		}           
			else {
				counter++;
			}			
              	}	                                             
        }  
	if (boolean) {
	       	printf("\t%d %s\n", counter, prev);
	}
	else {
		printf("%s\n", prev);
	}
        free(buffer);                                           
        free(prev);	
        return 0;
}	
