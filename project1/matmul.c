#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Matrix multiplication command
// Alp Kural 71959

int main(int argc, char *argv[]) {
	
	char buffer[100];
	strcpy(buffer, argv[1]);
	char *dimension = strtok(buffer, ",");
	int row1 = atoi(dimension);
	dimension = strtok(NULL, ",");
	int col1 = atoi(dimension);
        
	strcpy(buffer, argv[2]);
	dimension = strtok(buffer, ",");	
	int row2 = atoi(dimension);
	dimension = strtok(NULL, ",");
	int col2 = atoi(dimension);

	if (col1 != row2) {
		printf("Cannot operate matrix multiplication!\n");
		printf("Column number of matrix1 not matching row number of matrix2!\n");
		return 1;
	}

	char *rows1[row1];
	char *rows2[row2];

	strcpy(buffer, argv[3]);
	char *row = strtok(buffer, ";");
	for (int ii = 0; ii < row1; ii++) {
		rows1[ii] = strdup(row);
		row = strtok(NULL, ";");
	}                         

	strcpy(buffer, argv[4]);
	row = strtok(buffer, ";");
	for (int ii = 0; ii < row2; ii++) {
        	rows2[ii] = strdup(row);	
		row = strtok(NULL, ";");
	} 

	float matrix1[row1][col1];
	float matrix2[row2][col2];
	float result[row1][col2];;
	
	for (int ii = 0; ii < row1; ii++) {
		char *val = strtok(rows1[ii], ",");
		for (int jj = 0; jj < col1; jj++) {
			matrix1[ii][jj] = atof(val);
			val = strtok(NULL, ",");
		}               
	}

        for (int ii = 0; ii < row2; ii++) {
        	char *val = strtok(rows2[ii], ",");
        	for (int jj = 0; jj < col2; jj++) {
        		matrix2[ii][jj] = atof(val);	
			val = strtok(NULL, ",");
        	}      
	}
	for (int ii = 0; ii < row1; ii++) {
		for (int jj = 0; jj < col2; jj++) {
			for (int kk = 0; kk < row2; kk++) {
				if (kk == 0) {
					result[ii][jj] = matrix1[ii][kk] * matrix2[kk][jj];
				}
				else {	
					result[ii][jj] += matrix1[ii][kk] * matrix2[kk][jj];
				}
			}
		}
	}

	printf("Result is:\n");
	for (int ii = 0; ii < row1; ii++) {
		for (int jj = 0; jj < col2; jj++) {
			printf("%10.2f ", result[ii][jj]);
		}
		printf("\n");
	}

	for (int ii = 0; ii < row1; ii++) {
		free(rows1[ii]);
	}
	for (int ii = 0; ii < row2; ii++) {
		free(rows2[ii]);
	}
	return 0;
}
