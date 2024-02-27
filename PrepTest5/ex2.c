#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
	int *letter, *digit, *special;
	pthread_mutex_t *mutexes;
	char *str;
} data;


// Unfinished: didn't implement digits and specials but the same idea 


void* func(void *arg)
{
	data dt = *((data *) arg);
	int l = 0, d = 0, s = 0;
	int i, len = strlen(dt.str);
	
	for(i = 0; i < len; i++)
	{
		if((dt.str[i] >= 'a' && dt.str[i] <= 'z') || (dt.str[i] <= 'Z' && dt.str[i] >= 'A'))
			l++;
	}
	if(l > 0)
	{
		pthread_mutex_lock(&dt.mutexes[0]);
		*(dt.letter) += l;
		pthread_mutex_unlock(&dt.mutexes[0]);
	}

}


int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("Not enough arguments");
		return 1;
	}

	// Allocated memory to pointers to shared memory
	// These 3 are poniters accesible to the threads where we'll stock the final results
	int* letters = malloc(sizeof(int));
	int* digits = malloc(sizeof(int));
	int* specials = malloc(sizeof(int));
	// Creating the threads (it's an array of threads)
	pthread_t *thr = malloc(sizeof(pthread_t) * (argc - 1));
	// Array of data strcuts where we'll offer the pointers for the results, mutexes and the needed string to analyze
	data *argus = malloc(sizeof(data) * (argc - 1));
	pthread_mutex_t *mutx = malloc(sizeof(pthread_mutex_t) * 3);

	for(int i = 0; i < 3; i++)
	{
		if(pthread_mutex_init(&mutx[i], NULL) < 0)
		{
			printf("Mutex problem");
			return 1;
		}
	}

	*letters = 0;
	*digits = 0;
	*specials = 0;

	for(int i = 0; i < argc - 1; i++)
	{
		argus[i].letter = letters;
		argus[i].digit = digits;
		argus[i].special = specials;
		argus[i].mutexes = mutx;
		argus[i].str = argv[i + 1];

		if(pthread_create(&thr[i], NULL, &func, (void*) &argus[i]) < 0)
		{
			printf("Create thread problem");
			return 1;
		}
	}

	for(int i = 0; i < argc - 1; i++)
		if(pthread_join(thr[i], NULL) < 0)
		{
			printf("Problem join thread");
			return 1;
		}

	printf("Total letters - %d\n", *letters);
	for(int i = 0; i < 3; i++)
		pthread_mutex_destroy(&mutx[i]);
	
	free(argus);
	free(thr);
	free(specials);
	free(letters);
	free(digits);
	return 0;
}
