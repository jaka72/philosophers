#include "header.h"

void	destroy_mutexes(t_philo *ph)
{
	int	i;

	pthread_mutex_destroy(&ph->d->mutex_time);
	pthread_mutex_destroy(&ph->d->mutex_print);
	i = 0;
	while (i < ph->d->nrfilos)
	{
		pthread_mutex_unlock(&ph->d->mutex_forks[i]);
		pthread_mutex_destroy(&ph->d->mutex_forks[i]);
		i++;
	}
}

void	free_all(t_philo *ph, t_data *d)
{
	destroy_mutexes(ph);
	if (ph->d->mutex_forks != NULL)
	{
		free(d->mutex_forks);
		d->mutex_forks = NULL;
	}
	if (ph->d != NULL)
	{
		free(d);
		d = NULL;
	}
	if (ph != NULL)
	{
		free(ph);
		ph = NULL;
	}
}
