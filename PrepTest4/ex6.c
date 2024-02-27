#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

//Gets a word and a file
//IN child performs grep and in parent prints all the resulted lines

int main(int argc, char* argv[])
{
	int p2c[2], c2p[2];
	if(pipe(p2c) == -1)
	{
		printf("Error at pipe");
		return 1;
	}

	if(pipe(c2p) == -1)
	{
		printf("Error in pipe");
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
		char w[50], f[50];
		int lwc, lfc;

		read(p2c[0], &lwc, sizeof(int));
		read(p2c[0], w, sizeof(char) * lwc + 1);
		printf("Child got word: %s\n", w);

		read(p2c[0], &lfc, sizeof(int));
		read(p2c[0], f, sizeof(char) * lfc + 1);
		printf("Child got file: %s\n", f);
		dup2(c2p[1], STDOUT_FILENO);

		execlp("grep", "grep", "-E", w,  f, NULL);

		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}

	close(p2c[0]);
	close(c2p[1]);

	char word[50], file[50];
	int lw, lf;
	printf("The word: ");
	fgets(word, 50, stdin);
	lw = strlen(word) - 1;
	word[lw] = '\0';

	printf("The file: ");
	fgets(file, 50, stdin);
	lf = strlen(file) - 1;
	file[lf] = '\0';

	printf("File - %s word - %s\n", file, word);

	write(p2c[1], &lw, sizeof(int));
	write(p2c[1], word, sizeof(char) * lw + 1);
	write(p2c[1], &lf, sizeof(int));
	write(p2c[1], file, sizeof(char) * lf + 1);
	close(p2c[1]);

	dup2(c2p[0], STDIN_FILENO);
	close(c2p[0]);

	char line[100];
	while(fgets(line, 100, stdin)){
		line[strlen(line) - 1] = '\0';
		printf("line: %s\n", line);
	}

	//close(c2p[1]);
	wait(0);
	return 0;
}

