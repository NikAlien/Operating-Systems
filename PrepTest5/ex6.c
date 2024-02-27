#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semph;

// Doesn't work on mac but on Linux it's okay

void* func(void *arg)
{
	int i = *(int *)arg;
	int banana = rand() % 11;
	sem_wait(&semph);
	sleep(2);
	printf("Thread %d took %d bananas\n", i, banana);
	sem_post(&semph);
	return NULL;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	pthread_t thr[17];
	int id[17];
	sem_init(&semph, 0, 5);

	for(int i = 0; i < 17; i++)
	{	id[i] = i;
		pthread_create(&thr[i], NULL, &func, &id[i]);
	}

	for(int i = 0; i < 17; i++)
		pthread_join(thr[i], NULL);

	sem_destroy(&semph);
	return 0;
}
