#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Sums two numbers with FIFO

int main(int argc, char* argv[])
{
	mkfifo("p2c", 0666);

	int pid = fork();
	if(pid == -1)
	{
		printf("Error at fork");
		return 1;
	}

	if(pid == 0)
	{
		int ch, x, y;
		ch = open("p2c", O_RDONLY);
		read(ch, &x, sizeof(int));
		read(ch, &y, sizeof(int));
		close(ch);

		printf("Child got: %d and %d\n", x, y);
		printf("The sum is: %d\n", x + y);

		exit(0);
	}

	int a,b,f;
	printf("1st number: ");
	scanf("%d", &a);
	printf("2nd number: ");
	scanf("%d", &b);

	f = open("p2c", O_WRONLY);
	write(f, &a, sizeof(int));
	write(f, &b, sizeof(int));
	close(f);

	wait(0);
	unlink("p2c");
	return 0;
}

