#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


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
	t_philo *ph;
	
	ph = philo;
	meals = 2;
	i = 0;
	if (ph->id % 2 == 0)
		usleep(2000);
	while (i < meals)
	{
		//printf("Philo ID %d\n", ph->id);

		pthread_mutex_lock(&ph->d->lockfork[ph->id]);
		printf("    %d has taken fork %d\n", ph->id, ph->id);

		pthread_mutex_lock(&ph->d->lockfork[(ph->id + 1) % ph->d->nrphilos]);
		printf("    %d has taken fork %d\n", ph->id, (ph->id + 1) % ph->d->nrphilos);

		printf("    %d eating\n", ph->id);
		usleep(10000);

		pthread_mutex_unlock(&ph->d->lockfork[ph->id]);
		pthread_mutex_unlock(&ph->d->lockfork[(ph->id + 1) % ph->d->nrphilos]);
		printf("    %d sleeping\n", ph->id);
		usleep(10000);
		i++;
	}
	return NULL;
}



int main(void)
{
	int		i;;
	t_philo	*ph;
	t_data	d;

	d.nrphilos	= 1;
	ph 			= malloc(sizeof(t_philo)         * d.nrphilos);
	d.lockfork	= malloc(sizeof(pthread_mutex_t) * d.nrphilos);


	i = 0;
	while (i < d.nrphilos)
	{
		if (pthread_mutex_init(&d.lockfork[i], NULL) != 0)
			printf("Error init mutex\n");
		i++;
	}


	i = 0;
	while (i < d.nrphilos)
	{
		ph[i].id = i;
		ph[i].d = &d;
		if ((pthread_create(&ph[i].thread, NULL, &life_cycle, (void*)&ph[i]) != 0))
			printf("Error creating thread\n");
		//usleep(100);
		i++;
	}


	i = 0;
	int err;
	while(i < d.nrphilos)
	{
		err = pthread_join(ph[i].thread, NULL);
		printf("err: %d\n", err);
		i++;
	}

	free(d.lockfork);
	free(ph);
	return 0;
}
