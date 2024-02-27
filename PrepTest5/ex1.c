#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

// create as many threads as there are coloumns in a matrix, 
// each thread sums the numbers of the given coloumn and prints it

pthread_t th[3];
int matrix[3][3];

void* calculate(void* id)
{
	int col = *(int*) id;
	int sum = 0;
	for(int j = 0; j < 3; j++)
		sum += matrix[j][col];
	printf("Thread %d: calculated sum %d\n", col, sum);
}

int main(int argc, char* argv[])
{
	int col[3];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			matrix[i][j] = i + j;
	

	for(int i = 0; i < 3; i++)
	{
		col[i] = i;
		if(pthread_create(&th[i], NULL, &calculate, &col[i]) != 0)
			return 1;
	}
	for(int i = 0; i < 3; i++)
		if(pthread_join(th[i], NULL) != 0)
			return 1;
	return 0;
}
