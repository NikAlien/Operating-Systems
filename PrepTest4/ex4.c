#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Reads words until empty line
// one child gets words with "oa"
// second child gets the rest 
// both calculate the sum of the lengths


int main(int argc, char* argv[])
{
	int pc1[2], pc2[2];
	if(pipe(pc1) == -1)
	{
		printf("error at pipe 1");
		return 1;
	}
	if(pipe(pc2) == -1)
	{
		printf("error at pipe 2");
		return 1;
	}

	int pid1 = fork();
	if(pid1 == -1)
	{
		printf("Error at fork");
		return 2;
	}
	if(pid1 == 0)
	{
		// First child ("oa words")
		close(pc1[1]);
		close(pc2[1]);
		close(pc2[0]);
		
		char w1[100];
		int l1, all = 0;
		while(1)
		{
			read(pc1[0], &l1, sizeof(int));
			if(l1 == 0)
				break;

			read(pc1[0], w1, sizeof(char) * l1);
			printf("Child 1 got: %s, len %d\n", w1, l1 - 1);
			all += (l1 - 1);
		}
		printf("Child 1 with 'oa' %d\n", all);
		close(pc1[0]);
		exit(0);
	}

	int pid2 = fork();
	if(pid2 == -1)
	{
		printf("Error at fork 2");
		return 2;
	}
	if(pid2 == 0)
	{
		close(pc1[0]);
		close(pc1[1]);
		close(pc2[1]);

		char w2[100];
		int l2, all2 = 0;
		while(1)
		{
			read(pc2[0], &l2, sizeof(int));
			if(l2 == 0)
				break;
			read(pc2[0], w2, sizeof(char) * l2);
			printf("Child 2 got: %s, len %d\n", w2, l2 - 1);
			all2 += (l2 - 1);
		}

		printf("Child 2 got words %d length\n", all2);
		close(pc2[0]);
		exit(0);
	}

	close(pc1[0]);
	close(pc2[0]);

	char word[100];
	int len;
	printf("Your word: ");
	fgets(word, 100, stdin);
	len = strlen(word);
	word[len - 1] = '\0';

	while(len != 1)
	{
		if(strstr(word, "oa") == NULL)
		{
			//printf("No child 1\n");
			write(pc2[1], &len, sizeof(int));
			write(pc2[1], word, sizeof(char) * len);
		}
		else
		{
			write(pc1[1], &len, sizeof(int));
			write(pc1[1], word, sizeof(char) * len);
		}
		sleep(1);
		printf("Your word: ");
		fgets(word, 100, stdin);
		len = strlen(word);
		word[len - 1] = '\0';
	}
	len = 0;
	write(pc2[1], &len, sizeof(int));
	write(pc1[1], &len, sizeof(int));

	close(pc1[1]);
	close(pc2[1]);
	wait(0);
	wait(0);
	return 0;

}

