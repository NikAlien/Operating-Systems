#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Reads numbers until gets N prime ones 
//Child checks if prime or not

int main(int argc, char* argv[])
{

	int p2c[2], c2p[2];
	if(pipe(p2c) == -1)
	{
		printf("Error at pipe1");
		return 1;
	}
	if(pipe(c2p) == -1)
	{
		printf("Error at pipe2");
		return 1;
	}

	int pid = fork();
	if(pid == -1)
	{
		printf("Error at fork");
		return 2;
	}

	if(pid == 0)
	{

		close(p2c[1]);
		close(c2p[0]);

		while(1)
		{
			int n, x, flag = 0;
			read(p2c[0], &n, sizeof(int));

			if(n == 0)
				break;

			read(p2c[0], &x, sizeof(int));
			if(x == 0 || x == 1)
				flag = 1;
			for(int i = 2; i <= x / 2; i++)
				if(n % i == 0)
				{
					flag = 1;
					break;
				}			
			write(c2p[1], &flag, sizeof(int));

		
		}

		close(p2c[0]);
		close(c2p[1]);
		return 0;
	}


	close(p2c[0]);
	close(c2p[1]);
	int N, nr, f;
	
	printf("Nr of primes: ");
	scanf("%d", &N);

	while(1)
	{
		write(p2c[1], &N, sizeof(int));
		if(N == 0)
			break;
		
		printf("Your number: ");
		scanf("%d", &nr);
		write(p2c[1], &nr, sizeof(int));
		read(c2p[0], &f, sizeof(int));

		if(f == 1)
			printf("%d is not prime\n", nr);
		else
		{
			printf("%d is prime\n", nr);
			N--;
		}
	}
	
	printf("Done\n");
	wait(0);
	close(p2c[1]);
	close(c2p[0]);
	return 0;

}
