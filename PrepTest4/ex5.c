#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

//


int main(int argc, char* argv[])
{
	int a2b[2], b2a[2];
	if(pipe(a2b) == -1)
	{
		printf("Error pipe");
		return 1;
	}
	if(pipe(b2a) == -1)
	{
		printf("Error pipe");
		return 1;
	}

	int child = fork();
       	if(child == -1)
	{
		printf("Error fork");
		return 2;
	}	

	if(child == 0)
	{
		// Process A
		int gchild = fork();
		if(gchild == -1)
		{
			printf("Error fork");
			return 2;
		}
		if(gchild == 0)
		{
			//Process B
			close(a2b[1]);
			close(b2a[0]);
			while(1)
			{				
				int nr = 0;
				read(a2b[0], &nr, sizeof(int));
				nr /= 3;
				write(b2a[1], &nr, sizeof(int));
				if(nr < 5)
					break;
			}
			close(a2b[0]);
			close(b2a[1]);
			exit(0);
		}

		close(a2b[0]);
		close(b2a[1]);


		int n;
		printf("Your number: ");
		scanf("%d", &n);
		if(n > 50 && n % 3 == 0)
		{
			while(1){
				write(a2b[1], &n, sizeof(int));
				read(b2a[0], &n, sizeof(int));
				printf("The number so far: %d\n", n);
				if(n < 5)
					break;
				
			
				if(n % 3 == 0)
					n += 0;
				else if(n % 3 == 1)
					n += 2;
				else 
					n += 1;
			}
		}
			

		close(a2b[1]);
		close(b2a[0]);
		wait(0);
		exit(0);
	
	}
	close(a2b[0]);
	close(a2b[1]);
	close(b2a[0]);
	close(b2a[1]);
	wait(0);
	return 0;
	
}

