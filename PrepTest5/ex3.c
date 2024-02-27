#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutx;
pthread_cond_t cond;
int* arr;
int n, id;

void* f1()
{
	pthread_mutex_lock(&mutx);
	while(id % 2 != 0)
		pthread_cond_wait(&cond, &mutx);

	while(id < n)
	{
		int nr = (rand() % 10) * 2;
		arr[id] = nr;
		id += 1;
		printf("\nT1: ");
		for(int i = 0; i < id; i++)
			printf("%d ", arr[i]);
		pthread_cond_signal(&cond);

		while(id % 2 != 0 && id < n)
			pthread_cond_wait(&cond, &mutx);
	}

	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutx);
	return NULL;
}

void* f2()
{
	pthread_mutex_lock(&mutx);
	while(id % 2 != 1)
		pthread_cond_wait(&cond, &mutx);

	while(id < n)
	{
		int nr = (rand() % 10) * 2 + 1;
		arr[id] = nr;
		id += 1;
		printf("\nT2: ");
		for(int i = 0; i < id; i++)
			printf("%d ", arr[i]);
		pthread_cond_signal(&cond);

		while(id % 2 != 1 && id < n)
			pthread_cond_wait(&cond, &mutx);
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutx);
	return NULL;
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Please provide one cmd line arg");
		return 1;
	}
	srandom(time(NULL));
	id = 0;
	n = atoi(argv[1]);
	arr = malloc(sizeof(int) * n);

	pthread_mutex_init(&mutx, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_t thr[2];

	pthread_create(&thr[0], NULL, f1, NULL);
	pthread_create(&thr[1], NULL, f2, NULL);

	pthread_join(thr[0], NULL);
	pthread_join(thr[1], NULL);
	pthread_mutex_destroy(&mutx);
	pthread_cond_destroy(&cond);
	free(arr);
	return 0;
}
