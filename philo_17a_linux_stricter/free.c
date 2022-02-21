#include "header.h"

int	msg_and_free(t_philo *ph, t_data *d, char *str, int ret)
{
	printf("%s\n", str);
	free_all(ph, d);
	return (ret);
}

void	destroy_mutexes(t_philo *ph)
{
	int	i;

	pthread_mutex_destroy(&ph->d->mutex_time);
	pthread_mutex_destroy(&ph->d->mutex_print);
	pthread_mutex_destroy(&ph->d->mutex_death);
	i = 0;
	while (i < ph->d->nrfilos)
	{
		pthread_mutex_destroy(&ph->d->mutex_forks[i]);
		i++;
	}
}

void	free_all(t_philo *ph, t_data *d)
{
	destroy_mutexes(ph);
	//printf("  From free All\n");
	if (ph->d->mutex_forks != NULL)
	{
		free(d->mutex_forks);
		d->mutex_forks = NULL;
	}
	if (ph != NULL)
	{
		free(ph);
		ph = NULL;
	}
}
