// #include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define NUMBER_OF_THREADS 11 /* Hint */
#define PUZZLE_SIZE 9

/* example puzzle */
int puzzle[PUZZLE_SIZE+1][PUZZLE_SIZE+1] = {
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0},
			{-1,0,0,0,0,0,0,0,0,0}
		};

/* data structure for passing data to threads */
typedef struct
{
	int thread_number;
	int x;
	int y;
} parameters;

/* print puzzle */ 
#define LINE "====================== \n"
#define COLLINE "\n___________________________________ \n"
#define NAME "||  SUM   CHECKER  || \n"
void print_grid(int grid[10][10])
{
    int i,j;
    printf(LINE);
    printf(NAME);
    printf(LINE);

	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
	        printf("|%1d |",grid[i][j]);
		}
        printf(COLLINE);
	}
    printf("\n");
}
// read file to check sudoku
void SetPuzzle(const char filename[]){
    FILE *file = fopen(filename,"r");
    int i,j,ch,num;
    for (i=0;i<=9;i++){
        for(j=0;j<=9;j++){
            while(((ch = getc(file)) != EOF)){
                if(ch == EOF) break;
                if(ch == ',') break;
                if(ch == '\n') break;
                ungetc(ch,file);
                fscanf(file,"%d",&num);
                if(num!=-1)
                    puzzle[i][j] = num;            
            } 
        }
    }
    print_grid(puzzle);
    return;
}
int main(int argc, char* argv[])
{
	int rv = 1; // flag to check answer
    // input the sudoku file
    SetPuzzle("test2.txt");

    int sum = 0;
    for(int j = 1; j <= 9; j++){
        sum += puzzle[1][j];
    }

    int sum_tmp = 0;
    for(int i = 2; i <= 9; i++){
        for(int j = 1; j <= 9; j++){
            sum_tmp += puzzle[i][j];
        }

        if(sum_tmp != sum){
            rv = 0;
            break;
        }else{
            sum_tmp = 0;
        }
    }

    for(int j = 1; j <= 9; j++){
        if(rv == 0) break;
        for(int i = 1; i <= 9; i++){
            sum_tmp += puzzle[i][j];
        }

        if(sum_tmp != sum){
            rv = 0;
            break;
        }else{
            sum_tmp = 0;
        }
    }

    for(int x = 1; x <= 3; x++){
        if(rv == 0) break;
        for(int y = 1; y <= 3; y++){
            for(int i = 3*x-2; i <= 3*x; i++){
                for(int j = 3*y-2; j <= 3*y; j++){
                    sum_tmp += puzzle[i][j];
                }
            }

            if(sum_tmp != sum){
                rv = 0;
                break;
            }else{
                sum_tmp = 0;
            }
        }
    }
    
	if (rv == 1)
		printf("Successful :) \n");
	else
		printf("Must check again! :( \n");

	return 0;
}
