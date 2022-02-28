#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int timetoeat 	= 200000;
int timetosleep = 200000;
int timetodie 	= 800000;

typedef struct s_data
{
	int				nrphilos;
	pthread_mutex_t	*lockfork;

} t_data;


typedef struct s_philo
{
	int				id;
	t_data			*d;
	pthread_t		thread;
} t_philo;



void* life_cycle(void *philo)
{
	int		i;
	int		meals;
	t_philo	*ph;
	
	ph = philo;
	meals = 3;
	i = 0;
	if (ph->id % 2 != 0)
		usleep(timetoeat - 1);
	while (i < meals)
	{

		pthread_mutex_lock(&ph->d->lockfork[ph->id]);
		pthread_mutex_lock(&ph->d->lockfork[(ph->id + 1) % ph->d->nrphilos]);

		printf("    %d has taken fork %d\n", ph->id, ph->id);
		printf("    %d has taken fork %d\n", ph->id, (ph->id + 1) % ph->d->nrphilos);

		printf("    %d eating\n", ph->id);
		usleep(timetoeat);

		pthread_mutex_unlock(&ph->d->lockfork[(ph->id + 1) % ph->d->nrphilos]);
		pthread_mutex_unlock(&ph->d->lockfork[ph->id]);
		printf("    %d sleeping\n", ph->id);
		usleep(timetosleep);

		i++;
	}
	return NULL;
}



int main(void)
{
	int		i, start;
	t_philo	*ph;
	t_data	d;

//	start 		= 1;
	start 		= 0;
	d.nrphilos	= 200 + start;

	ph 			= malloc(d.nrphilos * sizeof(t_philo));
	d.lockfork	= malloc(d.nrphilos * sizeof(pthread_mutex_t));

	i = start;
	while (i < d.nrphilos)
	{
		if (pthread_mutex_init(&d.lockfork[i], NULL) != 0)
			printf("Error init mutex\n");
		i++;
	}


	i = start;
	while (i < d.nrphilos)
	{
		ph[i].id = i;
		ph[i].d = &d;
		if ((pthread_create(&ph[i].thread, NULL, &life_cycle, (void*)&ph[i]) != 0))
			printf("Error creating thread\n");
		i++;
	}


	i = start;
	while(i < d.nrphilos)
	{
		pthread_join(ph[i].thread, NULL);
		i++;
	}

	free(d.lockfork);
	free(ph);
	return 0;
}
