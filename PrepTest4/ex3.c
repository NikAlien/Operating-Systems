#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

//Creates n child processes

int main(int argc, char* argv[])
{
	int n;
	printf("Nr of processes: ");
	scanf("%d", &n);

	for(int i = 0; i < n; i++)
	{
		int pid = fork();
		if(pid == 0)
		{
			printf("%d. Child %d with parent %d\n", i, getpid(), getppid());
			exit(0);
		}
		else if(pid == -1)
		{
			printf("No child created\n");
		}	
	}
	for(int i = 0; i < n; i++)
		wait(0);
	printf("Done!\n");
	return 0;

}

