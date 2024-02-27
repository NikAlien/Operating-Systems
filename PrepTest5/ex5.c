#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int ind, sentEnd;
char result[100];

pthread_mutex_t mutx;

void* func(void* argc)
{
	char str[100];
       	strcpy(str, (char*) argc);	
	while(sentEnd >= 0){

		pthread_mutex_lock(&mutx);
		int wordStart = sentEnd;
		//printf("Got index: %d\n", sentEnd);
		while(wordStart >= 0 && str[wordStart] != ' ')
		{
			wordStart--;
		}
	
		int i = wordStart + 1;
		while(i <= sentEnd)
		{
			result[ind] = str[i];
			ind++;
			i++;
		}
		result[ind++] = ' ';
		sentEnd = wordStart - 1;
			
		//printf("Result so far: %s\n", result);
		pthread_mutex_unlock(&mutx);

	}
	return NULL;
}

int main(int argc, char* argv[])
{
	char sent[100];
	pthread_t thr[5];
	pthread_mutex_init(&mutx, NULL);
	printf("Enter your sentence: \n");
	scanf("%[^\n]s", sent);

	int space = 0;
	for(int i = 0; i < strlen(sent); i++)
		if(sent[i] == ' ')
			space++;
	if(space < 5)
	{
		printf("need to be minimum 6 words\n");
		return 1;
	}

	sentEnd = strlen(sent) - 1;
	ind = 0;
	for(int i = 0; i < 5; i++)
		if(pthread_create(&thr[i], NULL, &func, (void *) sent) < 0)
		{
			printf("Problem with thread creation\n");
			return 1;
		}

	for(int i = 0; i < 5; i++)
		pthread_join(thr[i], NULL);


	printf("Result: %s\n", result);
	pthread_mutex_destroy(&mutx);
	return 0;
}
