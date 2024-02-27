#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void* upCase(void* arg)
{
	char str[100];
	strcpy(str, (char*) arg);
	
	for(int i = 0; i < strlen(str); i++)
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;

	printf("Word: %s\n", str);

	return NULL;
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("No cmd line arg");
		return 1;
	}

	pthread_t *thr = malloc(sizeof(pthread_t) * (argc - 1));
	for(int i = 0; i < argc - 1; i++)
		pthread_create(&thr[i], NULL, upCase, (void*) argv[i + 1]);

	for(int i = 0; i < argc - 1; i++)
		pthread_join(thr[i], NULL);

	free(thr);
	return 0;
}
