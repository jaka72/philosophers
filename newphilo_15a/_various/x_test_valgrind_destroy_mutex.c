#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <float.h>




int	main(void)
{

	pthread_mutex_t	mforks[3];




	pthread_mutex_init(&mforks[0], NULL);
	pthread_mutex_init(&mforks[1], NULL);
	pthread_mutex_init(&mforks[2], NULL);
	//pthread_mutex_destroy(&mforks[0]);
	



	return (0);
}