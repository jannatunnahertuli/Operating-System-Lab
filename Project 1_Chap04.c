/*Books Reference: Operating System Concepts 10th Edition – Silberschatz
Chapter:04,PROJECT 01: SUDKO SOLUTION VALIDATOR
ID: 1705031
NAME:JANNATUNNAHER
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int valid[27] = {0};

typedef struct {
	int row;
	int column;
} parameters;

int sudo[9][9] = {
	{6, 2, 4, 5, 3, 9, 1, 8, 7},
	{5, 1, 9, 7, 2, 8, 6, 3, 4},
	{8, 3, 7, 6, 1, 4, 2, 9, 5},
	{1, 4, 3, 8, 6, 5, 7, 2, 9},
	{9, 5, 8, 2, 4, 7, 3, 6, 1},
	{7, 6, 2, 3, 9, 1, 4, 5, 8},
	{3, 7, 1, 9, 5, 6, 8, 4, 2},
	{4, 9, 6, 1, 8, 2, 5, 7, 3},
	{2, 8, 5, 4, 7, 3, 9, 1, 6}
};

void *ColumnCheck(void* p) {
	parameters *ps=(parameters*) p;
	int row=ps->row;
	int col=ps->column;
	if (row!=0 || col>8) {
		printf("Invalid\n");
		pthread_exit(NULL);
	}

	int ar[9]={0};
	int i;
	for (i=0; i<9; i++) {
		int n=sudo[i][col];
		if (n<1 || n>9 || ar[n-1]==1) {
			pthread_exit(NULL);
		} else {
			ar[n-1]=1;
		}
	}
	valid[18+col]=1;
	pthread_exit(NULL);
}


void *RowCheck(void* p) {
	parameters *ps=(parameters*) p;
	int row=ps->row;
	int col=ps->column;
	if (col!=0 || row> 8) {
		printf("Invalid\n");
		pthread_exit(NULL);
	}
	int ar[9] = {0};
	int i;
	for (i=0; i<9; i++) {

		int n=sudo[row][i];
		if (n<1 || n>9 || ar[n-1]==1) {
			pthread_exit(NULL);
		} else {
            ar[n-1] = 1;
		}
	}

	valid[9+row]=1;
	pthread_exit(NULL);
}

void *Check3x3(void* p) {
	parameters *ps= (parameters*) p;
	int row=ps->row;
	int col=ps->column;
	if (row> 6 || row%3!=0 || col>6 || col%3!=0) {
		printf("Invalid\n");
		pthread_exit(NULL);
	}
	int ar[9] = {0};
	int i, j;
	for (i=row; i<row+3; i++) {
		for (j=col; j<col+3; j++) {
			int n=sudo[i][j];
			if (n<1 || n>9 || ar[n-1]==1) {
				pthread_exit(NULL);
			} else {
				ar[n-1]=1;
			}
		}
	}
	valid[row+col/3]=1;
	pthread_exit(NULL);
}

int main() {
	pthread_t threads[27];

	int in=0;
	int i,j;
	printf("Welcome to Sudoko Solution Validator\n\n");
    for(i=0; i<9; i++)
    {
        for(j=0; j<9; j++)
        {
           printf("%d ",sudo[i][j]);
        }
        printf("\n");
    }
	for (i=0; i<9; i++) {
		for (j= 0; j<9; j++) {
			if (i%3 == 0 && j%3 == 0) {
				parameters *data =(parameters *) malloc(sizeof(parameters));
				data->row=i;
				data->column=j;
				pthread_create(&threads[in++], NULL, Check3x3, data); // 3x3 check
			}
			if (i==0) {
				parameters *columnData = (parameters *) malloc(sizeof(parameters));
				columnData->row=i;
				columnData->column=j;
				pthread_create(&threads[in++], NULL, ColumnCheck, columnData);	// column check
			}
			if (j==0) {
				parameters *rowData=(parameters *) malloc(sizeof(parameters));
				rowData->row=i;
				rowData->column=j;
				pthread_create(&threads[in++], NULL,RowCheck, rowData); // row check
			}
		}
	}

	for (i = 0; i < 27; i++) {
		pthread_join(threads[i], NULL);
	}


	for (i = 0; i < 27; i++) {
		if (valid[i] == 0) {
			printf("Bad try! This Sudoku solution is invalid!\n");
			return EXIT_SUCCESS;
		}
	}
	printf("Good try! This Sudoku solution is valid!\n");
	return EXIT_SUCCESS;
}
