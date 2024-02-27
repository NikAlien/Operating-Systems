#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//send two numbers to child that sums them and sends the sum back to parent

int main(int argc, char* argv[]) 
{
	int p2c[2], c2p[2];
	if(pipe(p2c) == -1)
	{
		printf("Error in pipe1");
		return 1;
	}
	if(pipe(c2p) == -1)
	{
		printf("Error in pipe2");
		return 1;
	}

	int pid = fork();
	if(pid == -1)
	{
		printf("Error in fork");
		return 2;
	}

	if(pid == 0)
	{	
		close(p2c[1]);
		close(c2p[0]);
		int a, b, sum;
		read(p2c[0], &a, sizeof(int));
		read(p2c[0], &b, sizeof(int));
		sum = a + b;
		write(c2p[1], &sum, sizeof(int));
		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}

	close(p2c[0]);
	close(c2p[1]);

	int x, y, sumP;
	printf("Number 1: ");
	scanf("%d", &x);
	printf("Number 2: ");
	scanf("%d", &y);
	
	write(p2c[1], &x, sizeof(int));
	write(p2c[1], &y, sizeof(int));
	read(c2p[0], &sumP, sizeof(int));
	
	close(p2c[1]);
	close(c2p[0]);

	printf("The sum is %d\n", sumP);
	wait(0);
	return(0);

}

