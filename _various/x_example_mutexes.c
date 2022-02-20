#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t	lock;
int counter	= 0;


typedef struct s_data
{
	int				x;
	int				nrphilos;
	int				dcounter;
	//pthread_mutex_t	singlelock;

} t_data;


typedef struct s_philo
{
	t_data			*d;
	pthread_t		thread;
	int				phcounter;
	int				id;
	pthread_mutex_t	*lockforks;

} t_philo;



void* cicle(void *philo)
{
	int		i;
	t_philo *ph;
	ph = philo;

	printf("cicle)\n");

	i = 0;
	while (i < 2)
	{
		pthread_mutex_lock(&ph->lockforks[i]);
		pthread_mutex_lock(&ph->lockforks[(i + 1) % ph->d->nrphilos]);

		printf("    cicle a)\n");



		// printf ("Loop count %d\n", i);
		// printf("Thread %d, loop %d\n", ph->id, i);
		// usleep(100000);
		// printf("Thread %d, loop %d\n", ph->id, i);

		// ph->phcounter += 1; // THIS IS UNIQUE TO EACH THREAD
		// printf("\n Thread %d: Job %d started\n", ph->id, ph->phcounter);
		// usleep(100000);
		// printf("\n Thread %d: Job %d finished\n", ph->id, ph->phcounter);
		
		// ph->d->dcounter += 1;
		// printf("\n Job %d started\n", ph->d->dcounter);
		// usleep(100000);
		// printf("\n Job %d finished\n", ph->d->dcounter);


	//	pthread_mutex_unlock(&ph->d->singlelock);
		pthread_mutex_unlock(&ph->lockforks[i]);
		pthread_mutex_unlock(&ph->lockforks[(i + 1) % ph->d->nrphilos]);
		i++;
	}
	return NULL;
}


int main(void)
{
	int		i = 0;
	int		err;
	t_philo	*ph;
	t_data	d;

	d.dcounter = 0;

	//d.x = 0;
	d.nrphilos = 2;
	ph = malloc(sizeof(t_philo) * d.nrphilos);

	ph->phcounter = 10;
	ph[0].phcounter = 5;
	ph[1].phcounter = 100;





	// i = 0;
	// if (pthread_mutex_init(&d.singlelock, NULL) != 0)
	// 	printf("\n mutex init failed\n");

	ph->lockforks = malloc(sizeof(pthread_mutex_t) * d.nrphilos);

	i = 0;
	while (i < d.nrphilos)
	{
		if (pthread_mutex_init(&ph->lockforks[i], NULL) != 0)
			printf("Error init mutex\n");
		i++;
	}

	printf("a)\n");


	i = 0;
	//while(i < d.nrphilos)
	while(i < 1)
	{
		printf("    i %d)\n", i);
		ph[i].id = i;
		ph[i].d = &d;
		err = pthread_create(&ph[i].thread, NULL, &cicle, (void*)&ph[i]);
		if (err != 0)
			printf("\ncan't create thread :[%s]", strerror(err));
		i++;
	}

	printf("b)\n");

	sleep(1);

	i = 0;
	//while(i < d.nrphilos)
	while(i < 1)
	{
		pthread_join(ph[i].thread, NULL);
		i++;
	}

	printf("END MAIN)\n");

	free(ph->lockforks);
	free(ph);
	return 0;
}
